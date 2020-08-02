#version 410 core
/*
out vec4 frag_color;

in vec3 resultPos;
in vec3 resultNorm;

void main() {
    vec3 lightDir = vec3(0, -1, 0);
    frag_color = vec4(resultPos, 1) * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}
*/


//RUVASHA
/*
#define MAXStep 10000
#define MAXDist 100.0
#define Eps 1e-5
#define myPi 3.141592654f/(2.0f)
#define ShConst 0.3
#define ObjNum 5
#define LightNum 2
#define ReflMax 4


float iTime = 1;
vec2 iMouse = vec2(0, 0);
vec2 iResolution = vec2(1280, 720);

vec3 baseCol = vec3(0.4,0.8,1.0);

struct ray{
	float dist;
	vec3 col;
	vec3 pos;
	bool hit;
	int num;
};

struct scene{
	float dist;
	int num;
};
    
bool reflectVec[ObjNum] = bool[ObjNum](bool(0), bool(1), bool(0), bool(1), bool(1));
bool refractVec[ObjNum] = bool[ObjNum] (bool(0), bool(0), bool(0), bool(0), bool(1));
vec4 lightPos[LightNum] = vec4[LightNum](vec4(-2.0, 20.0, 2.0, 0.0), vec4 (0.0, 5.0, 3.0, 2.0));
vec3 lightI[LightNum] = vec3[LightNum](vec3(1.0, 1.0, 1.0), vec3(2.0, 2.0, 2.0));
//vec3(lightPos[i].x, lightPos[i]. y + lightPos[i].w*cos(iTime*myPi/4.0), lightPos[i].z)

float getSphDist(vec3 p, vec3 center, float R){
    return length(p - center) - R;
}

float getBoxDist(vec3 p, vec3 center, vec3 boxPar){
    vec3 d = abs(p - center)  - boxPar;
    return min(0.0, max(d.x, max(d.y, d.z))) + length(max(d, 0.0));
}

float getPrismDist( vec3 p, vec3  center, vec2 prismPar )
{
    vec3 q = abs(p - center);
    return max(q.z-prismPar.y,max((q.x*0.866025+q.y*0.5),q.y)-prismPar.x);
}



scene getSceneDist (vec3 p){
    scene s;
    
    vec3 sph1 = vec3(3.0, 1.0, 5.0);
    float r1 = 1.0;
    vec3 box1 = vec3(-2.0, 0.25, 10.0 );
    vec3 box1Par = vec3(1.0, 0.5, 1.0);
    vec3 box2 = vec3(2.5, 2.0, 12.5);
    vec3 box2Par = vec3(10.0, 3.0, 1.0);
    vec3 prism1 = vec3(-7.0, 2.0, 8.0);
    vec2 prism1Par = vec2(1.0, 1.5);
    
    float planeDist = p.y;
    float sph1Dist = getSphDist(p, sph1, r1);
    float box1Dist = getBoxDist(p, box1, box1Par);
    float box2Dist = getBoxDist(p, box2, box2Par);
    float prism1Dist = getPrismDist(p, prism1, prism1Par);
    
    float m1 = min(box2Dist, box1Dist);
    float m2 = min(sph1Dist, m1);
    float m3 = min(prism1Dist, m2);
    
    
    if (planeDist< m3){
        s.num = 0; s.dist = planeDist;
    }
    else 
        if (prism1Dist < m2){
            s.num = 4; s.dist = prism1Dist;
        }else
        	if (sph1Dist < m1){
        		s.num = 1; s.dist = sph1Dist;
    		}
    		else
        	    if (box1Dist < box2Dist){
        	    s.num = 2; s.dist = box1Dist;
    			}
    			else{
        	    s.num  =3; s.dist = box2Dist;
        	    }
        
    
    
    return s;
}



ray RayMarching (vec3 rSrc, vec3 rDir, float maxDist){
    

	vec3 currP = rSrc;
	scene SD = getSceneDist(currP);
	float closestObjDist = SD.dist;
	float dist = .0;
	int i = 1;
	while ((i < MAXStep)&&(dist < maxDist)&&(closestObjDist > Eps))
	{
		dist = dist + closestObjDist;
		currP = rSrc + rDir*dist;
		SD = getSceneDist(currP);
		closestObjDist = SD.dist;
		i++;
	}
    
    float n =2.0;
    float px = floor(currP.x/n);
    float pz = floor(currP.z/n);
        px = abs(currP.x - n*px)/n;
    	pz = abs(currP.z - n*pz)/n;
    
    vec3 color[ObjNum] = vec3[ObjNum](vec3(px, 1.0 ,pz),
                                          vec3(1.0, 1.0, 0.3), vec3(0.8, 0.55, 0.2),
                                     	  vec3(1.0, 0.6, 0.6), vec3(0.3, 1.0, 1.0));

	ray ray1;
	ray1.hit = closestObjDist <= Eps;
	ray1.dist = dist;
	
	if (!ray1.hit) ray1.col = baseCol;
	else ray1.col = color[SD.num];

	ray1.pos = currP;
	ray1.num = SD.num;

	return ray1;
}

vec3 normal(vec3 pos){
	vec3 e = vec3(Eps, .0, .0);

	vec3 p1 = pos + e.xyz;
	vec3 p2 = pos - e.xyz;
	vec3 p3 = pos + e.yxz;
	vec3 p4 = pos - e.yxz;
	vec3 p5 = pos + e.yzx;
	vec3 p6 = pos - e.yzx;

	float dx = getSceneDist(p1).dist - getSceneDist(p2).dist;
	float dy = getSceneDist(p3).dist - getSceneDist(p4).dist;
	float dz = getSceneDist(p5).dist - getSceneDist(p6).dist;

	return normalize(vec3(dx, dy, dz)/(2.0*Eps));
}



vec3 getLight(vec3 pos){
 
    
    vec3 col = vec3(1.0, 1.0, 1.0);
    for (int i=0; i < LightNum; i++){
        	vec3 lTo = vec3(lightPos[i].x, lightPos[i]. y + lightPos[i].w*cos(iTime*myPi/4.0), lightPos[i].z)
                - pos;
        	ray light = RayMarching(pos + 2.0*Eps*normal(pos), normalize(lTo), length(lTo) + 1.0);
            float sp = dot(normal(pos), normalize(lTo));
            
        	if ((!light.hit)&&(sp>=ShConst)) 
                //if (sp>= 0.98) col = vec3(2.0, 2.0, 2.0);
                //else 
                    col*= sp;
            else col*= ShConst;
            
            col *= lightI[i];
            //col = col*min(1.0, 100.0*alpha/length(lTo)/length(lTo));
    	}
    return col;
}

vec3 glare(vec3 pos){
    
    vec3 col = vec3(1.0, 1.0, 1.0);
    for (int i=0; i < LightNum; i++){
        vec3 lTo =  vec3(lightPos[i].x, lightPos[i]. y + lightPos[i].w*cos(iTime*myPi/4.0), lightPos[i].z)
            - pos;
        ray light = RayMarching(pos + 2.0*Eps*normal(pos), normalize(lTo), length(lTo) + 1.0);
        float sp = dot(normal(pos), normalize(lTo));    
        if ((!light.hit)&&(sp>= 0.999 )) col = vec3(5.0, 5.0, 5.0);
    	}
    return col;
}


vec3 reflection(vec3 pos, vec3 initDir){
    
    vec3 resCol = vec3(1.0, 1.0, 1.0);
    bool go = bool(1);
    int i =1;
    vec3 raydir = initDir;
    ray ray1;
    vec3 norm;
    
    while (go &&(i<=ReflMax)){
        norm  =normal(pos);
        raydir = reflect(raydir, norm);
        ray1 = RayMarching(pos + 2.0*Eps*norm, raydir, MAXDist);
        if (!ray1.hit) {go =bool(0); resCol *= baseCol; }
        else {
            resCol *= ray1.col;
            if (reflectVec[ray1.num]){ 
                //raydir = normalize(ray1.pos - pos); 
                pos = ray1.pos; i++;
            }
        	else {go = bool(0); resCol *= getLight(ray1.pos);
                 }
        }
    }
    if (i > ReflMax) {
        resCol *= getLight(ray1.pos);
                     }
    return resCol;
}


vec3 getRayDir(vec2 fragCoord){
    vec2 uv = (fragCoord - 0.5*iResolution.xy)/iResolution.y;
    vec3 rayDirAbs = normalize(vec3(uv.xy, 1.0));
    float phi = iMouse.y/iResolution.y ;
    float psi = iMouse.x/iResolution.x ;
    
    mat3 rotX = mat3(1.0 , 0.0, 0.0,  0.0, cos(phi), -sin(phi), 0.0, sin(phi), cos(phi) );
    mat3 rotY = mat3(cos(psi), 0.0, -sin(psi), 0.0, 1.0, 0.0, sin(psi), 0.0, cos(psi));
    
    return rotX * rotY * rayDirAbs;
    
    
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ){
    vec3 rayDir = getRayDir(fragCoord);
	vec3 cameraPos = vec3(1.0, 3.0, -2.0 );
    
    ray myRay = RayMarching(cameraPos, rayDir, MAXDist);
    vec3 col1;
    vec3 col= myRay.col;
    if (myRay.hit){
        if (reflectVec[myRay.num]){
            col1 = reflection(myRay.pos, normalize(rayDir));
        	col = col1*0.5 + 0.3*myRay.col;
            col *= glare(myRay.pos);
        }
        else
    	col *= getLight(myRay.pos);
    }
    
    for (int i=0; i< LightNum; i++){
	if (dot(normalize(-cameraPos + vec3(lightPos[i].x, lightPos[i]. y + lightPos[i].w*cos(iTime*myPi/4.0), lightPos[i].z) ),
            rayDir) > 1.0 -4.0*Eps)
		col = lightI[i];
    }
    
    fragColor = vec4(col,1.0);
}

out vec4 frag_color;

in vec3 resultPos;
in vec3 resultNorm;

void main() {
    vec4 fragColor;
    vec2 fragCoord = resultPos.xy;
    iTime = resultPos.z;
    fragCoord.x *= 1280;
    fragCoord.y *= 720;
    mainImage(fragColor, fragCoord);
    vec3 lightDir = vec3(0, -1, 0);
    frag_color = fragColor * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}
*/

//OURS

#define OBJECTS_IN_SCENE 10
#define eps 0.01
#define LIGHTS_AM 2

float iTime = 1;
vec2 iMouse = vec2(0, 0);
vec2 iResolution = vec2(1280, 720);

struct material {
    vec3 color;
    bool glass;
    bool mirror;
    bool light;
    float ior;
    bool isNULL;
    vec3 params;
};

struct obj {
    float sd;
    material mat;
};

material newMaterial(vec3 co, bool gl, bool mi, bool li, float io, vec3 pa) {
    material ret;
    ret.color = co;
    ret.glass = gl;
    ret.mirror = mi;
    ret.light = li;
    ret.ior = io;
    ret.isNULL = false;
    ret.params = pa;
    return ret;
}

obj newObject(float s, material m) {
    obj ret;
    ret.sd = s;
    ret.mat = m;
    return ret;
}

bool line(vec2 p, vec2 s, vec2 e) {
    if (abs((p.x-s.x)/(e.x-s.x) - (p.y-s.y)/(e.y-s.y)) < 0.03 && p.x < max(e.x, s.x) && p.x > min(e.x, s.x))
        return true;
    return false;
}

float circle(float lvl) {
    return 3.14 * 2. * lvl / 5.;
}

bool star(vec3 p, float radi, float parAng) {
    vec2 a1 = vec2(radi * cos(parAng), radi * sin(parAng));
    vec2 a2 = vec2(radi * cos(circle(1.) + parAng), radi * sin(circle(1.) + parAng));
    vec2 a3 = vec2(radi * cos(circle(2.) + parAng), radi * sin(circle(2.) + parAng));
    vec2 a4 = vec2(radi * cos(circle(3.) + parAng), radi * sin(circle(3.) + parAng));
    vec2 a5 = vec2(radi * cos(circle(4.) + parAng), radi * sin(circle(4.) + parAng));
    
    if (abs(sqrt(p.x * p.x + p.z * p.z)) < radi && abs(sqrt(p.x * p.x + p.z * p.z)) > radi - 0.1 || line(p.xz, a1, a3) || line(p.xz, a3, a5) || line(p.xz, a5, a2) || line(p.xz, a2, a4) || line(p.xz, a4, a1))
        return true;
    return false;
}

bool superstar(vec3 p, float radi, float parAng) {
    bool ret = star(p, radi, parAng);
    for (int i = 0; i < 5; i++)
        ret = ret || star(p - vec3(cos(parAng + circle(float(i))), 0., sin(parAng + circle(float(i)))) * radi, radi * 0.2, -parAng);
    return ret;
}

bool megastar(vec3 p, float radi, float parAng) {
    return star(p, radi * 0.65, parAng + circle(1.) / 2.) || superstar(p, radi, parAng);
}

material checkerMaterial(vec3 p) {
    float ang = atan(p.z / p.x);
    
    float a = 5.;
    float k = 5.;
    float b = iTime * 2.;
    float r = a * cos(k * ang + b);
    material ret;
    ret.params = vec3(1., 0.8, 0.);
    
    int x = int(p.x);
            int z = int(p.z);
            if (p.x < 0.)
                x--;
            if (p.z < 0.)
                z--;
    		if (x % 2 == 0 && z % 2 == 0 || x % 2 != 0 && z % 2 != 0) {
                ret.color = vec3(1.);
            }
            else
                ret.color = vec3(0.3);
    if (megastar(p, 3.5, iTime))
        ret.color = vec3(1., 0., 0.);
    return ret;
}

material colorMaterial(vec3 col) {
    return newMaterial(col, false, false, false, 1., vec3(1., 0.6, 16.));
}

material lightMaterial() {
    return newMaterial(vec3(1.), false, false, true, 1., vec3(1.));
}

material mirrorMaterial(vec3 col) {
    return newMaterial(col, false, true, false, 1., vec3(1.));
}

material glassMaterial(vec3 col, float ior) {
    return newMaterial(col, true, false, false, ior, vec3(1., 1., 16.));
}

float sdSphere(vec3 p, vec3 pos, float r) {
     return length(p - pos) - r;
}

float sdBox(vec3 p, vec3 pos, vec3 box) {
    return length(max(abs(p - pos) - box, 0.));
}

float sdCapsule(vec3 p, vec3 pos, vec3 a, vec3 b, float r) {
    p -= pos;
    vec3 ab = b - a;
    vec3 ap = p - a;
    float t = dot(ab, ap) / dot(ab, ab);
    t = clamp(t, 0., 1.);
    
    vec3 c = a + ab * t;
    return length(p - c) - r;
}

float sdFloor(vec3 p, float y) {
    return abs(p.y - y);
}

float sdRoi(vec3 p) {
    float t = iTime * 0.5;
    
	vec4 c = 0.5*vec4(cos(t),cos(t*1.1),cos(t*2.3),cos(t*3.1));
    vec4 z = vec4( p, 0.0 );
	vec4 nz;
    
	float md2 = 1.0;
	float mz2 = dot(z,z);

	for(int i=0;i<10;i++)
	{
		md2*=4.0*mz2;
	    nz.x=z.x*z.x-dot(z.yzw,z.yzw);
		nz.yzw=2.0*z.x*z.yzw;
		z=nz+c;

		mz2 = dot(z,z);
		if(mz2>4.0)
        {
			break;
        }
	}

	return 0.25*sqrt(mz2/md2)*log(mz2);
}

const vec3 va = vec3(  0.0,  0.57735,  0.0 );
const vec3 vb = vec3(  0.0, -1.0,  1.15470 );
const vec3 vc = vec3(  1.0, -1.0, -0.57735 );
const vec3 vd = vec3( -1.0, -1.0, -0.57735 );

float sdFract(vec3 p, vec3 pos) {
    p -= pos;
	float a = 0.0;
    float s = 1.0;
    float r = 1.0;
    float dm;
    vec3 v;
    for( int i=0; i < 6; i++ )
	{
	    float d, t;
		d = dot(p-va,p-va);              v=va; dm=d; t=0.0;
        d = dot(p-vb,p-vb); if( d<dm ) { v=vb; dm=d; t=1.0; }
        d = dot(p-vc,p-vc); if( d<dm ) { v=vc; dm=d; t=2.0; }
        d = dot(p-vd,p-vd); if( d<dm ) { v=vd; dm=d; t=3.0; }
		p = v + 2.0*(p - v); r*= 2.0;
		a = t + 4.0*a; s*= 4.0;
	}
	
	return (sqrt(dm)-1.0)/r;
}

float sdAtomic(vec3 p, vec3 pos) {
    float ret = sdSphere(p, pos + vec3(sin(iTime * 2.) * 2., sin(iTime * 2.) * 1.1, cos(iTime * 2.) * 2.), .1);
    ret = min(ret, sdSphere(p, pos + vec3(cos(iTime * 2. + 3.14 / 2.) * 2., sin(iTime * 2. + 3.14 / 2.) * 1.1, sin(iTime * 2. + 3.14 / 2.) * 2.), .1));
    ret = min(ret, sdSphere(p, pos + vec3(sin(iTime * 2. + 3.14 / 2.) * 2., cos(iTime * 2. + 3.14 / 2.) * 2., cos(iTime * 2. + 3.14 / 2.) * 1.1), .1));
    ret = min(ret, sdSphere(p, pos + vec3(sin(iTime * 2.) * 2., sin(iTime * 2.) * 2., cos(iTime * 2.) * 0.5), .1));
    return ret;
}

float sdSth(vec3 p, vec3 pos) {
    return min(sdSphere(p, pos, 0.85), sdBox(p, pos, vec3(0.7, 0.7, 0.7)));
}

obj Fract(vec3 p) {
    return newObject(sdFract(p, vec3(0., 1., 0.)), colorMaterial(vec3(1., 0., 0.9)));
}

obj Roi(vec3 p) {
    return newObject(sdRoi((p.yxz - vec3(5., 0., 0.))), colorMaterial(vec3(1., 0., 0.)));
}

obj scene[OBJECTS_IN_SCENE];

vec4 lights[LIGHTS_AM];

const material Sky = material(vec3(0.5, 0.9, 1.), false, false, true, 1., false, vec3(1.));

obj Light(vec3 p, int i) {
    return newObject(sdSphere(p, lights[i].xyz, 0.08), lightMaterial());
}

obj Atomic(vec3 p) {
    return newObject(sdAtomic(p, vec3(0., 5., 0.)), mirrorMaterial(vec3(1., 0.8, 0.8)));
}

obj SphereG(vec3 p) {
    return newObject(sdSphere(p, vec3(3.4, 1., 0.), 0.6), glassMaterial(vec3(1., 0.9, 0.9), 1.51));
}

obj SphereM(vec3 p) {
    return newObject(sdSphere(p, vec3(-5.7, 0.62, 0.), 0.6), mirrorMaterial(vec3(1., 0.9, 0.9)));
}

obj Tabletka(vec3 p) {
    return newObject(sdCapsule(p, vec3(0., 0.5, 5.7), vec3(-0.2, -0.4, -0.4), vec3(0.2, 0.4, 0.3), 0.2), colorMaterial(vec3(1., 0., 0.)));
}

obj Box(vec3 p) {
    //return newObject(sdBox(p, vec3(0., 0.4, -5.7), vec3(0.5, 0.5, 0.5)), mirrorMaterial(vec3(0.8, 1., 0.8)));
    return newObject(sdSth(p, vec3(0., 0.4, -5.7)), mirrorMaterial(vec3(0.8, 1., 0.8)));
}

void initLights() {
    lights[0] = vec4(0., 2.1, 0., 1.);
    lights[1] = vec4(sin(iTime) * 8., 2.5, cos(iTime), 5.);
}

void initScene(vec3 p) {
    scene[0] = Light(p, 0);
    scene[1] = newObject(sdFloor(p, 0.), checkerMaterial(p));
    scene[2] = Fract(-p + vec3(0., 1.8, 0.));
    scene[3] = Roi(p);
    scene[4] = Atomic(p);
    scene[5] = Light(p, 1);
    scene[6] = SphereG(p);
    scene[7] = SphereM(p);
    scene[8] = Tabletka(p);
    scene[9] = Box(p);
}

float sdf(vec3 p, out material mat, bool ignoreLight) {
    initScene(p);
    float sdf = 1000000.;
    mat = Sky;
    for (int i = 0; i < OBJECTS_IN_SCENE; i++) {
        if (scene[i].sd < sdf) {
            if ((!scene[i].mat.light || !ignoreLight) && !scene[i].mat.isNULL) {
            	sdf = scene[i].sd;
            	mat = scene[i].mat;
            }
        }
    }
    return sdf;
}

float sdf(vec3 p, out material mat) {
    return sdf(p, mat, false);
}

vec3 sdf_n(vec3 p) {
    vec3 res = vec3(0.);
    
    material ignore;
    res.x = sdf(p + vec3(eps, 0., 0.), ignore) - sdf(p, ignore);
    res.y = sdf(p + vec3(0., eps, 0.), ignore) - sdf(p, ignore);
    res.z = sdf(p + vec3(0., 0., eps), ignore) - sdf(p, ignore);
    
    return normalize(res);
}

float ao(vec3 p, vec3 n) {
    float ret = 0.;
    material ignore;
    float weight = 0.5;
    for (int i = 1; i <= 5; i++) {
        float d = 0.1 * float(i);
        ret += weight * (1. - (d - sdf(p + p * n, ignore, true)));
        weight *= 0.5;
    }
    
    return ret;
}

float shadow(vec3 p, vec3 l, float t_max) {
    float t = 0.1;
    material ignore;
    float ret = 1.;
    
    for (int i = 0; i < 256; i++) {
        if (t > t_max)
            break;
        
        float d = sdf(p + t * l, ignore, true);
        if (d < eps) {
            return 0.;
        }
        t += d;
        
        //МЯГКИЕ ТЕНИ
        ret = min(ret, 20. * d / t);
    }
    return ret;
}

float calcShadows(vec3 ob) {
    float ret = 0.;
    for (int i = 0; i < LIGHTS_AM; i++) {
        vec3 l = normalize(lights[i].xyz - (ob));
        ret += shadow(ob, l, length(lights[i].xyz - ob) - eps);
    }
    return ret / float(LIGHTS_AM);
}

vec3 intersect(out vec3 ro, out vec3 rd, out material mat) {
    float t = 0.;
    mat = Sky;
    vec3 odd = vec3(1.);
    for (int i = 0; i < 128; i++) {
        material cur = Sky;
        float d = sdf(ro + t * rd, cur);
        if (d < eps) {
            if (cur.mirror) {
                vec3 norm = sdf_n(ro + rd * t);
                ro = ro + rd * t;
                rd = normalize(reflect(rd, norm));
                ro += rd * eps * 2.;
                t = 0.;
                odd *= cur.color;
            }
            else {
                if (cur.glass) {
                    ro = ro + rd * t;
                    vec3 norm = sdf_n(ro);
                    
                    rd = refract(rd, norm, 1. / cur.ior);
                    float le = 0.;
                    material ignore;
                    float dd;
                    while ((dd = sdf(ro + rd * le, ignore)) < eps && ignore == cur) {
                        le += 0.01;
                    }
                    ro += rd * le;
                    
                    rd = refract(rd, norm, cur.ior);
                    
                    ro += rd * eps;
                    
                    odd *= cur.color;
                    t = 0.;
                }
                else {
                    
                    vec3 pos = ro + rd * t;
                    vec3 norm = sdf_n(pos);
                    
                    float ao = ao(pos, norm) * 0.3;
                    mat = cur;
                    if (!mat.light) {
                        for (int i = 0; i < LIGHTS_AM; i++) {

                            vec3 lig = normalize(lights[i].xyz - pos);
                            float amb = mat.params.x * clamp( 0.5+0.5*norm.y, 0.0, 1.0 );
                            float dif = mat.params.y * clamp( dot( norm, lig ), 0.0, 1.0 );
                            float bac = clamp( dot( norm, normalize(vec3(-lig.x,0.0,-lig.z))), 0.0, 1.0 )*clamp( 1.0-pos.y,0.0,1.0);

                            float sh = 1.;

                            vec3 brdf = vec3(0.0);
                            brdf += 0.20*amb*vec3(0.10,0.11,0.13)*ao;
                            brdf += 0.20*bac*vec3(0.15,0.15,0.15)*ao;
                            brdf += 1.20*dif*vec3(1.);
                            
                            brdf *= lights[i].w;

                            float pp = clamp( dot( reflect(rd,norm), lig ), 0.0, 1.0 );
                            float spe = (mat.params.z == 0. ? 0. : sh*pow(pp, mat.params.z));
                            float fre = ao * pow( clamp(1.0+dot(norm,rd),0.0,1.0), 2.0 );

                            mat.color = mat.color * brdf + vec3(1.0) * mat.color * spe + 0.2*fre*(0.5+0.5*mat.color);
                        }
                        mat.color *= calcShadows(pos) + ao * 0.3;
                    }
                	break;
                }
            }
        }
        t += d;
    }
    mat.color *= odd;
    return ro + rd * t;
}

float calcLights(vec3 ob, vec3 n) {
    float ret = 0.;
    for (int i = 0; i < LIGHTS_AM; i++) {
        float rv = 0.;
        vec3 v = normalize(ob);
        vec3 l = normalize(lights[i].xyz - ob);
        vec3 r = reflect(v, n);
        rv += max(dot(l, n), 0.);
        rv += dot(l, n);
        rv += pow(max(dot(l, r), 0.0), 3.), 1. - rv;
        ret += rv * lights[i].w;
    }
    return ret;
}

vec3 rdPos = vec3(0., 0., 0.);
vec3 cameraPos = vec3(9., 8., -5.);

void camera() {
    initLights();
    cameraPos = vec3(sin(iTime * 0.02) * 10., 8., cos(iTime * 0.02) * 10.);
}
vec3 fromMouse() {
    rdPos += vec3(-sin((iMouse.x - iResolution.x / 2.) / 120.) * 8., (iMouse.y - iResolution.y / 2.) / 10., -cos((iMouse.x - iResolution.x / 2.) / 120.) * 8.);
    //return rdPos;
    return vec3(0, 0, 1);
}

in vec3 camPos;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = 2.0 * fragCoord/iResolution.xy - 1.0;
    uv.x *= iResolution.x / iResolution.y;
    
    material mat;
    
    camera();
    
    vec3 ro = camPos;//cameraPos;
    vec3 at = fromMouse();
    vec3 cam_z = normalize(at - ro);
    vec3 cam_x = normalize(cross(vec3(0, 1, 0), cam_z));
    vec3 cam_y = cross(cam_z, cam_x);
    vec3 rd = normalize(uv.x * cam_x+ uv.y * cam_y +  1.73 * cam_z);
    
    
    vec3 pos = intersect(ro, rd, mat);
    
    vec3 color = mat.color;
    
    color = mix(color, Sky.color, smoothstep(1., 60., length(pos)));
    
    fragColor = vec4(mat.light ? mat.color : color, 1.);
}

out vec4 frag_color;

in vec3 resultPos;
in vec3 resultNorm;

void main() {
    vec4 fragColor;
    vec2 fragCoord = resultPos.xy + vec2(+0.5, -0.5);
    iMouse = vec2(1280 / 2, 720 / 2);
    iTime = 10000;
    fragCoord.x *= 1280;
    fragCoord.y *= -720;
    mainImage(fragColor, fragCoord);
    vec3 lightDir = vec3(0, -1, 0);
    frag_color = fragColor * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}