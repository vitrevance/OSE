#version 410 core
//RUVASHA

in vec3 resultPos;
in vec3 resultNorm;
in vec3 camPos;

#define MAXStep 10000
#define MAXDist 100.0
#define Eps 1e-5
#define myPi 3.141592654f/(2.0f)
#define ShConst 0.3
#define ObjNum 5
#define LightNum 2
#define ReflMax 4


float iTime = 1;
vec2 iResolution = vec2(1280, 720);
vec2 iMouse = iResolution / 2;

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
    //vec2 uv = (fragCoord - 0.5*iResolution.xy)/iResolution.y;
    //vec3 rayDirAbs = normalize(vec3(uv.xy, 1.0));
    //float phi = iMouse.y/iResolution.y ;
    //float psi = iMouse.x/iResolution.x ;
    
    //mat3 rotX = mat3(1.0 , 0.0, 0.0,  0.0, cos(phi), -sin(phi), 0.0, sin(phi), cos(phi) );
    //mat3 rotY = mat3(cos(psi), 0.0, -sin(psi), 0.0, 1.0, 0.0, sin(psi), 0.0, cos(psi));

    //return rotX * rotY * rayDirAbs;
    
    return normalize(resultPos - camPos);
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

void main() {
    vec4 fragColor;
    vec2 fragCoord = (resultPos.xy + vec2(0.5, 0.5)) * vec2(1280, 720);
    iTime = camPos.z;
    mainImage(fragColor, fragCoord);
    vec3 lightDir = vec3(0, -1, 0);
    frag_color = fragColor * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}