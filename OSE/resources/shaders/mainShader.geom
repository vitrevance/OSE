#version 410 core

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec4 outVertex[];
in vec4 outBase1[];
in vec4 outBase2[];
in vec4 outBase3[];
in vec2 outUVVe[];
in vec2 outUVB1[];
in vec2 outUVB2[];
in vec2 outUVB3[];
in vec4 translate[];

out vec3 resultPos;
out vec3 resultNorm;
out vec2 uv_coord;

uniform mat4 uMatView;
uniform mat4 uMatProjection;
uniform float uFWProjection;

struct Vert4 {
    vec4 pos;
    vec2 uv;
};

struct Edge {
    Vert4 a, b;
};

struct Vert3 {
    vec3 pos;
    vec2 uv;
};

struct Edge3 {
    Vert3 a, b;
};

void main() {
    mat4 matView = inverse(uMatView);
    mat4 matPVM = uMatProjection * matView;

    int intersections = 0;
	bool allin = true;
    Edge edges[6];
    edges[0] = Edge(Vert4(outVertex[0], outUVVe[0]), Vert4(outBase1[0], outUVB1[0]));
    edges[1] = Edge(Vert4(outVertex[0], outUVVe[0]), Vert4(outBase2[0], outUVB2[0]));
    edges[2] = Edge(Vert4(outVertex[0], outUVVe[0]), Vert4(outBase3[0], outUVB3[0]));
    edges[3] = Edge(Vert4(outBase1[0], outUVB1[0]), Vert4(outBase2[0], outUVB2[0]));
    edges[4] = Edge(Vert4(outBase2[0], outUVB2[0]), Vert4(outBase3[0], outUVB3[0]));
    edges[5] = Edge(Vert4(outBase3[0], outUVB3[0]), Vert4(outBase1[0], outUVB1[0]));

    Vert3 points[4];

    for (int i = 0; i < 6; i++) {
        Edge e = edges[i];
        if (sign(uFWProjection - e.a.pos.w) + sign(uFWProjection - e.b.pos.w) == 0.0) {
            if (sign(uFWProjection - e.b.pos.w) != 0.0) {
				points[intersections].pos = e.a.pos.xyz + ((e.b.pos.xyz - e.a.pos.xyz) * (uFWProjection - e.a.pos.w) / (e.b.pos.w - e.a.pos.w));
                points[intersections].uv = e.a.uv + ((e.b.uv - e.a.uv) * (uFWProjection - e.a.pos.w) / (e.b.pos.w - e.a.pos.w));
                intersections++;
				allin = false;
			}
        }
		else {
			allin = false;
		}
    }
	if (allin) {
		resultNorm = normalize(cross(outBase1[0].xyz - outBase2[0].xyz, outBase1[0].xyz - outBase3[0].xyz));
		gl_Position = matPVM * vec4(outBase1[0].xyz, 1);
		resultPos = outBase1[0].xyz;
        uv_coord = outUVB1[0];
		EmitVertex();
        //resultNorm = normalize(cross(outBase2[0].xyz - outBase3[0].xyz, outBase2[0].xyz - outVertex[0].xyz));
		gl_Position = matPVM * vec4(outBase2[0].xyz, 1);
		resultPos = outBase2[0].xyz;
        uv_coord = outUVB2[0];
		EmitVertex();
		gl_Position = matPVM * vec4(outBase3[0].xyz, 1);
		resultPos = outBase3[0].xyz;
        uv_coord = outUVB3[0];
		EmitVertex();
        //resultNorm = normalize(cross(outBase3[0].xyz - outVertex[0].xyz, outBase3[0].xyz - outBase1[0].xyz));
		gl_Position = matPVM * vec4(outVertex[0].xyz, 1);
		resultPos = outVertex[0].xyz;
        uv_coord = outUVVe[0];
		EmitVertex();
		gl_Position = matPVM * vec4(outBase1[0].xyz, 1);
		resultPos = outBase1[0].xyz;
        uv_coord = outUVB1[0];
		EmitVertex();
        //resultNorm = normalize(cross(outVertex[0].xyz - outBase1[0].xyz, outVertex[0].xyz - outBase2[0].xyz));
		gl_Position = matPVM * vec4(outBase2[0].xyz, 1);
		resultPos = outBase2[0].xyz;
        uv_coord = outUVB2[0];
		EmitVertex();
		EndPrimitive();
	}
    else if (intersections == 3) {
		resultNorm = normalize(cross(points[0].pos - points[1].pos, points[0].pos - points[2].pos));
        resultNorm *= sign(dot(resultNorm, normalize(points[0].pos - translate[0].xyz)));
        gl_Position = matPVM * vec4(points[0].pos, 1);
		resultPos = points[0].pos;
        uv_coord = points[0].uv;
        EmitVertex();
        gl_Position = matPVM * vec4(points[1].pos, 1);
		resultPos = points[1].pos;
        uv_coord = points[1].uv;
        EmitVertex();
        gl_Position = matPVM * vec4(points[2].pos, 1);
		resultPos = points[2].pos;
        uv_coord = points[2].uv;
        EmitVertex();
        EndPrimitive();
    }
    else if (intersections == 4) {
        Edge3 d1, d2;
        d1.a.pos = points[0].pos;
        d1.b.pos = points[1].pos;
        d2.a.pos = points[2].pos;
        d2.b.pos = points[3].pos;
        d1.a.uv = points[0].uv;
        d1.b.uv = points[1].uv;
        d2.a.uv = points[2].uv;
        d2.b.uv = points[3].uv;
        
        if (length(points[0].pos - points[1].pos) > length(points[0].pos - points[2].pos)) {
            if (length(points[0].pos - points[1].pos) > length(points[0].pos - points[3].pos)) {
                d1.a.pos = points[0].pos;
                d1.b.pos = points[1].pos;
                d2.a.pos = points[2].pos;
                d2.b.pos = points[3].pos;
                d1.a.uv = points[0].uv;
                d1.b.uv = points[1].uv;
                d2.a.uv = points[2].uv;
                d2.b.uv = points[3].uv;
            }
            else {
                d1.a.pos = points[0].pos;
                d1.b.pos = points[3].pos;
                d2.a.pos = points[1].pos;
                d2.b.pos = points[2].pos;
                d1.a.uv = points[0].uv;
                d1.b.uv = points[3].uv;
                d2.a.uv = points[1].uv;
                d2.b.uv = points[2].uv;
            }
        }
        else {
            if (length(points[0].pos - points[2].pos) > length(points[0].pos - points[3].pos)) {
                d1.a.pos = points[0].pos;
                d1.b.pos = points[2].pos;
                d2.a.pos = points[1].pos;
                d2.b.pos = points[3].pos;
                d1.a.uv = points[0].uv;
                d1.b.uv = points[2].uv;
                d2.a.uv = points[1].uv;
                d2.b.uv = points[3].uv;
            }
            else {
                d1.a.pos = points[0].pos;
                d1.b.pos = points[3].pos;
                d2.a.pos = points[1].pos;
                d2.b.pos = points[2].pos;
                d1.a.uv = points[0].uv;
                d1.b.uv = points[3].uv;
                d2.a.uv = points[1].uv;
                d2.b.uv = points[2].uv;
            }
        }
        
		resultNorm = normalize(cross(d1.a.pos - d1.b.pos, d2.a.pos - d2.b.pos));
        resultNorm *= sign(dot(resultNorm, normalize(d2.a.pos - translate[0].xyz)));
        gl_Position = matPVM * vec4(d2.a.pos, 1);
		resultPos = d2.a.pos;
        uv_coord = d2.a.uv;
        EmitVertex();
        gl_Position = matPVM * vec4(d1.a.pos, 1);
		resultPos = d1.a.pos;
        uv_coord = d1.a.uv;
        EmitVertex();
        gl_Position = matPVM * vec4(d1.b.pos, 1);
		resultPos = d1.b.pos;
        uv_coord = d1.b.uv;
        EmitVertex();
        gl_Position = matPVM * vec4(d2.b.pos, 1);
		resultPos = d2.b.pos;
        uv_coord = d2.b.uv;
        EmitVertex();
		gl_Position = matPVM * vec4(d2.a.pos, 1);
		resultPos = d2.a.pos;
        uv_coord = d2.a.uv;
        EmitVertex();
		gl_Position = matPVM * vec4(d1.a.pos, 1);
		resultPos = d1.a.pos;
        uv_coord = d1.a.uv;
        EmitVertex();
        EndPrimitive();
        
    }
}