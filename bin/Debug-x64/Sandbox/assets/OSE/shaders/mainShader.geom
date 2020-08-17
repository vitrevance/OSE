#version 410 core

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec4 outVertex[];
in vec4 outBase1[];
in vec4 outBase2[];
in vec4 outBase3[];

out vec3 resultPos;
out vec3 resultNorm;

uniform mat4 uMatView;
uniform mat4 uMatProjection;
uniform float uFWProjection;

struct Edge {
    vec4 a, b;
};

struct Edge3D {
    vec3 a, b;
};

void main() {
    mat4 matView = inverse(uMatView);
    mat4 matPVM = uMatProjection * matView;

    int intersections = 0;
	bool allin = true;
    Edge edges[6];
    edges[0] = Edge(outVertex[0], outBase1[0]);
    edges[1] = Edge(outVertex[0], outBase2[0]);
    edges[2] = Edge(outVertex[0], outBase3[0]);
    edges[3] = Edge(outBase1[0], outBase2[0]);
    edges[4] = Edge(outBase2[0], outBase3[0]);
    edges[5] = Edge(outBase3[0], outBase1[0]);

    vec3 points[4];

    for (int i = 0; i < 6; i++) {
        Edge e = edges[i];
        if (sign(uFWProjection - e.a.w) + sign(uFWProjection - e.b.w) == 0.0) {
            if (sign(uFWProjection - e.b.w) != 0.0) {
				points[intersections] = e.a.xyz + ((e.b.xyz - e.a.xyz) * (uFWProjection - e.a.w) / (e.b.w - e.a.w));
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
		EmitVertex();
		gl_Position = matPVM * vec4(outBase2[0].xyz, 1);
		resultPos = outBase2[0].xyz;
		EmitVertex();
		gl_Position = matPVM * vec4(outBase3[0].xyz, 1);
		resultPos = outBase3[0].xyz;
		EmitVertex();
		gl_Position = matPVM * vec4(outVertex[0].xyz, 1);
		resultPos = outVertex[0].xyz;
		EmitVertex();
		gl_Position = matPVM * vec4(outBase1[0].xyz, 1);
		resultPos = outBase1[0].xyz;
		EmitVertex();
		gl_Position = matPVM * vec4(outBase2[0].xyz, 1);
		resultPos = outBase2[0].xyz;
		EmitVertex();
		EndPrimitive();
	}
    else if (intersections == 3) {
		resultNorm = -normalize(cross(points[0] - points[1], points[0] - points[2]));
        gl_Position = matPVM * vec4(points[0], 1);
		resultPos = points[0];
        EmitVertex();
        gl_Position = matPVM * vec4(points[1], 1);
		resultPos = points[1];
        EmitVertex();
        gl_Position = matPVM * vec4(points[2], 1);
		resultPos = points[2];
        EmitVertex();
        EndPrimitive();
    }
    else if (intersections == 4) {
        Edge3D d1, d2;
        d1.a = points[0];
        d1.b = points[1];
        d2.a = points[2];
        d2.b = points[3];
        if (length(points[0] - points[1]) > length(points[0] - points[2])) {
            if (length(points[0] - points[1]) > length(points[0] - points[3])) {
                d1.a = points[0];
                d1.b = points[1];
                d2.a = points[2];
                d2.b = points[3];
            }
            else {
                d1.a = points[0];
                d1.b = points[3];
                d2.a = points[1];
                d2.b = points[2];
            }
        }
        else {
            if (length(points[0] - points[2]) > length(points[0] - points[3])) {
                d1.a = points[0];
                d1.b = points[2];
                d2.a = points[1];
                d2.b = points[3];
            }
            else {
                d1.a = points[0];
                d1.b = points[3];
                d2.a = points[1];
                d2.b = points[2];
            }
        }
		resultNorm = -normalize(cross(d1.a - d1.b, d2.a - d2.b));
        gl_Position = matPVM * vec4(d2.a, 1);
		resultPos = d2.a;
        EmitVertex();
        gl_Position = matPVM * vec4(d1.a, 1);
		resultPos = d1.a;
        EmitVertex();
        gl_Position = matPVM * vec4(d1.b, 1);
		resultPos = d1.b;
        EmitVertex();
        gl_Position = matPVM * vec4(d2.b, 1);
		resultPos = d2.b;
        EmitVertex();
		gl_Position = matPVM * vec4(d2.a, 1);
		resultPos = d2.a;
        EmitVertex();
		gl_Position = matPVM * vec4(d1.a, 1);
		resultPos = d1.a;
        EmitVertex();
        EndPrimitive();
        
    }
}