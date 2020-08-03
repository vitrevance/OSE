#version 410 core
//OURS

in vec3 resultPos;
in vec3 camPos;
in vec3 resultNorm;

float iTime = 1000;

//vec4 lamp3 = vec4(2., 1.5, -1., 0.2);
//vec4 lamp2 = vec4(-2., 1.5, -1., 0.2);
vec3 skyColor = vec3(0.5, 0.9, 1.);
vec3 albedo = vec3(0.8);

float inTime() {
    return iTime * 1.;
}

bool matReflect(int matid) {
    return matid == 1 || matid == 5;
}

vec3 circCoords(float r, vec3 add) {
    return vec3(sin(inTime() + add.x) * r, sin(inTime() + add.y), cos(inTime() + add.z) * r);
}

#define LIGHTS_AM 2
vec4 lamps[LIGHTS_AM];

void initLights() {
    lamps[0] = vec4(0., 2., -2., 0.2);//vec4(circCoords(4., vec3(0., 0., 0.)) + vec3(0., 2., 0.), 0.2);
    lamps[1] = vec4(0., 0., -6., 0.2);
}

vec3 matColor(int matid) {
    vec3 matcol = vec3(0., 1., 0.4);;
    switch(matid) {
            case 1:
            matcol = vec3(1., 1., 1.);
            break;
            case 2:
            matcol = vec3(0.8, 1., 0.);
            break;
            case 3:
            matcol = vec3(0.9, 0.2, 0.);
            break;
            case 4:
            matcol = vec3(0., 0., 1.);
            break;
            case 0:
            matcol = vec3(100000.);
            break;
        case 5:
        matcol = vec3(1., 1., 1.);
        break;
        case 6:
        matcol = vec3(0.1, 0.1, 0.1);
        break;
        case 7:
        matcol = vec3(1., 1., 1.);
        break;
        }
    return matcol;
}

const vec3 va = vec3(  0.0,  0.57735,  0.0 );
const vec3 vb = vec3(  0.0, -1.0,  1.15470 );
const vec3 vc = vec3(  1.0, -1.0, -0.57735 );
const vec3 vd = vec3( -1.0, -1.0, -0.57735 );

float sdFract(vec3 p) {
	float a = 0.0;
    float s = 1.0;
    float r = 1.0;
    float dm;
    vec3 v;
    for( int i=0; i < 1; i++ )
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

float distanceToNearestSurface(vec3 p){
	float s = 1.0;
    vec3 d = abs(p) - vec3(s);
    return min(max(d.x, max(d.y,d.z)), 0.0)
        + length(max(d,0.0));
}

float distanceToNearestSurface2(vec3 p){
	float s = 1.0;
    vec3 d = abs(p) - vec3(s);
    float ret = min(min(d.y, max(d.x,d.z)), 0.0) + length(abs(d));
    return ret;
}

float sdSphere(vec3 p, float r) {
    return length(p) - r;
}

float sdCapsule(vec3 p, vec3 a, vec3 b, float r) {
    vec3 ab = b - a;
    vec3 ap = p - a;
    float t = dot(ab, ap) / dot(ab, ab);
    t = clamp(t, 0., 1.);
    
    vec3 c = a + ab * t;
    return length(p - c) - r;
}

float sdTorus(vec3 p, vec2 r) {
    float x = length(p.xz) - r.x;
    return length(vec2(x, p.y)) - r.y;
}

float sdBox(vec3 p, vec3 box) {
    return length(max(abs(p) - box, 0.));
}

float julia(vec3 p) {
    float t = iTime;
    
	vec4 c = 0.5*vec4(sin(t),cos(t*1.1),max(tan(t * 1.5), sin(t * 3.5)),sin(t*3.1) * cos(t) * max(tan(t * 1.5), sin(t * 3.5)));
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

float sdLights(vec3 p) {
    float light_sdf = length(p - lamps[0].xyz) - lamps[0].w;
    for (int i = 1; i < LIGHTS_AM; i++)
    	light_sdf = min(light_sdf, length(p - lamps[i].xyz) - lamps[i].w);
    return light_sdf;
}

float sdf(vec3 p, out int matid, bool ignoreLights) {
    float fractTriang_sdf = sdBox(p - vec3(0., sin(inTime()) + 0.5, -8.), vec3(5., 3., 0.5));;//sdFract(p - vec3(0., 0.5, 0.));
    float sphere_sdf = length(p - vec3(3., 1., 0.)) - 0.8;
    float center_sdf = length(p - vec3(3., 1., -2.)) - 0.5;
    float cube_sdf = sdBox(p - vec3(-1.5, sin(inTime()) + 0.5, -1.), vec3(0.6));
    float floor_sdf = abs(p.y + 0.8);
    float capsule_sdf = sdCapsule(p, circCoords(4., vec3(1.8)), circCoords(4., vec3(1.8)) + vec3(0.5), 0.3);
    float lamp_sdf = sdLights(p);
    
    float sdf = min(sphere_sdf, center_sdf);
    sdf = min(sdf, cube_sdf);
    sdf = min(sdf, capsule_sdf);
    sdf = min(sdf, floor_sdf);
    sdf = min(sdf, fractTriang_sdf);
    
    if (!ignoreLights) {
    	sdf = min(sdf, lamp_sdf);
    }
    
    if (sdf == sphere_sdf || sdf == center_sdf) {
        matid = 1;
    }
    else
    if (sdf == cube_sdf)
        matid = 2;
    else
    if (sdf == capsule_sdf)
        matid = 4;
    else
    if (sdf == lamp_sdf)
        matid = 0;
    else
    if (sdf == fractTriang_sdf)
        matid = 5;
    else
        if (sdf == floor_sdf) {
            int x = int(p.x);
            int z = int(p.z);
            if (p.x < 0.)
                x--;
            if (p.z < 0.)
                z--;
            if (x % 2 == 0 && z % 2 == 0 || x % 2 != 0 && z % 2 != 0)
                matid = 6;
            else
                matid = 7;
        }
    else
        matid = -2;
    return sdf;
}

float sdf(vec3 p, out int matid) {
    return sdf(p, matid, false);
}

vec3 sdf_n(vec3 p) {
    vec3 res = vec3(0);
    
    int ignore;
    res.x = sdf(p + vec3(0.001, 0., 0.), ignore) - sdf(p, ignore);
    res.y = sdf(p + vec3(0., 0.001, 0.), ignore) - sdf(p, ignore);
    res.z = sdf(p + vec3(0., 0., 0.001), ignore) - sdf(p, ignore);
    
    return normalize(res);
}

float shadow(vec3 p, vec3 l) {
    float t = 0.1;
    float t_max = 100.;
    int ignore;
    float ret = 1.;
    
    for (int i = 0; i < 256; i++) {
        if (t > t_max)
            break;
        
        float d = sdf(p + t * l, ignore, true);
        if (d < 0.01) {
            return 0.;
        }
        t += d;
        ret = min(ret, 20000. * d / t);
    }
    return ret;
}

float intersect(in vec3 ro, in vec3 rd, out int matid) {
    float t = 0.;
    matid = -1;
    for (int i = 0; i < 256; i++) {
        int cur_matid = -1;
        float d = sdf(ro + t * rd, cur_matid);
        if (d < 0.001) {
            matid = cur_matid;
            break;
        }
        t += d;
    }
    return t;
}

float ao(vec3 p, vec3 n) {
    float e = 0.1;
    
    float ret = 0.;
    int ignore;
    float weight = 0.5;
    for (int i = 1; i <= 5; i++) {
        float d = e * float(i);
        ret += weight * (1. - (d - sdf(p + p * n, ignore)));
        weight *= 0.5;
    }
    
    return ret;
}

float triang(float gip, float side) {
    return sqrt(pow(gip, 2.) - pow(side, 2.));
}

float calcLights(in vec3 ob, in vec3 n) {
    /*
    float ret = 0.;
    for (int i = 0; i < LIGHTS_AM; i++) {
        vec3 l = normalize(lamps[i].xyz - (ob));
        ret += dot(l, n);
    }
    return sqrt(ret);*/
    
    float ret = 0.;
    for (int i = 0; i < LIGHTS_AM; i++) {
        vec3 v = normalize(ob);
        vec3 l = normalize(lamps[i].xyz - ob);
        vec3 r = reflect(v, n);
        ret += max(dot(l, n), 0.);
        ret += dot(l, n);
        ret += pow(max(dot(l, r), 0.0), 3.), 1. - ret;
    }
    return ret;
}

float calcShadows(in vec3 ob, in vec3 n) {
    float ret = 0.;
    for (int i = 0; i < LIGHTS_AM; i++) {
        vec3 l = normalize(lamps[i].xyz - (ob));
        ret += shadow(ob, l);
    }
    return ret / float(LIGHTS_AM);
}

vec3 reflections(vec3 ob, vec3 rd, int thisMat, int maxDep) {
    vec3 color = vec3(1.);
    int material;
    vec3 norm = sdf_n(ob);
    vec3 ref = normalize(reflect(rd, norm));
    for (int i = 0; i < maxDep; i++) {
    	float t = intersect(ob + norm * 0.02, ref, material);
        if (material == -1) {
            color *= skyColor;
            break;
        }
        if (matReflect(material)) {
            ob = ob + ref * t;
            norm = sdf_n(ob + ref * t);
            ref = normalize(reflect(ref, norm));
            color *= matColor(material);
        }
        else {
            color *= matColor(material);
            norm = sdf_n(ob + ref * t);
            if (material != 0) {
                float light = calcLights(ob + ref * t, norm) * calcShadows(ob + ref * t, norm);
            	color *= light + ao(ob + ref * t, norm) * vec3(0.3);
                color *= albedo;
            }
            break;
        }
    }
    return color * matColor(thisMat);
}
/*
vec3 rdPos = vec3(0., 0., 0.);
vec3 cameraPos = vec3(0., 5., 0.);

vec3 fromMouse() {
    rdPos += vec3(-sin((iMouse.x - iResolution.x / 2.) / 120.) * 8., (iMouse.y - iResolution.y / 2.) / 10., -cos((iMouse.x - iResolution.x / 2.) / 120.) * 8.);
    return rdPos;
}

bool keyPressed(int key) {
    float val = textureLod( iChannel0, vec2( (float(key)+.5)/256.0, .75 ), 0.0 ).x;
    return val > 0.5;
}

vec3 fromKey() {
    if (keyPressed(88)) {
        cameraPos.x += sin(iTime) * 6.;
        rdPos.x += sin(iTime) * 6.;
    }
    if (keyPressed(90)) {
        cameraPos.z += sin(iTime) * 6.;
        rdPos.z += sin(iTime) * 6.;
    }
    if (keyPressed(89)) {
        cameraPos.y += sin(iTime) * 4.;
        rdPos.y += sin(iTime) * 4.;
    }
    return cameraPos;
}
*/
vec3 render(in vec2 fragCoord) {
    
    initLights();
    // Normalized pixel coordinates (from 0 to 1)
    //vec2 uv = 2.0 * fragCoord/iResolution.xy - 1.0;
    //uv -= .5;
    //uv.x *= iResolution.x / iResolution.y;
    // Time varying pixel color
    //vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    //vec3 ro = fromKey();//fromMouse();//vec3(0., 5., 2.); //camera origins
    //vec3 at = fromMouse();//vec3(0., 3., -6.);
    //vec3 cam_z = normalize(at - ro);
    //vec3 cam_x = normalize(cross(vec3(0, 1, 0), cam_z));
    //vec3 cam_y = cross(cam_z, cam_x);
    //vec3 rd = normalize(uv.x * cam_x+ uv.y * cam_y +  1.73 * cam_z);
    vec3 ro = vec3(0., 5., 2.);
    vec3 rd = normalize(resultPos - camPos);
    vec3 col = skyColor;
    
    int matid = -1;
    
    float t = intersect(ro, rd, matid);
    if (matid == 0)
        return vec3(1.);
    if (matid != -1) {
        vec3 n = sdf_n(ro + t * rd);
        vec3 light_color = vec3(1.);
        float projected_ratio = 0.;
        /*
        vec3 lamp = vec3(sin(iTime) * 8., 1., cos(iTime) * 8.);
        vec3 n = sdf_n(ro + t * rd);
        vec3 l = normalize(lamp - (ro + rd * t));
        float projected_ratio += dot(l, n) * 0.;
        
        vec3 lamp2 = vec3(0., 0.9, 0.);
        vec3 l2 = normalize(lamp2- (ro + rd * t));
        projected_ratio += dot(l2, n) * 1.;
		*/
        vec3 ob = (ro + rd * t);
        //vec3 l3 = normalize(lamp3.xyz - (ro + rd * t));
        //projected_ratio += dot(l3, n);
        projected_ratio += calcLights(ob, n);
        //float shadow_l3 = shadow(ro + t * rd, l3);// * lamp3.w;
        
        float shadows = calcShadows(ob, n);//shadow_l3;
        vec3 lights = light_color * projected_ratio * shadows;//(shadow(ro + t * rd, l) * 0. + shadow(ro + t * rd, l2) * lamp3.w);
        vec3 occlusion = ao(ro + t * rd, n) * vec3(0.3);
        
        vec3 matcol = matColor(matid);
        col = albedo * (lights + occlusion);
        col = col * matcol;
        if (matReflect(matid)) {
            col = reflections(ob, rd, matid, 5);
        }
    }
    return col;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 col = vec3(0.);
    col += render(fragCoord);
   //Anti-aliasing
    /*col += render(fragCoord + vec2(0.25, 0.25));
    col += render(fragCoord - vec2(0.25, 0.25));
    col += render(fragCoord + vec2(0.25, -0.25));
    col += render(fragCoord - vec2(0.25, -0.25));
    col /= 4.;*/
    fragColor = vec4(col, 1.);
}

out vec4 frag_color;

void main() {
    vec4 fragColor = vec4(0, 1, 0, 1);
    vec2 fragCoord = (resultPos.xy + vec2(0.5, 0.5)) * vec2(1280, 720);
    iTime = 1000;//camPos.z;
    mainImage(fragColor, fragCoord);
    vec3 lightDir = vec3(0, -1, 0);
    frag_color = fragColor * ( -dot(resultNorm, lightDir) + 1 ) / 2;
}