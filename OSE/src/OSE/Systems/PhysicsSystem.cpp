#include <OSE/Systems/PhysicsSystem.h>

namespace OSE {
	void PhysicsSystem::add(RigidBody* rigidBody) {
		this->m_physicsBodies.insert(rigidBody);
	}

	void PhysicsSystem::remove(RigidBody* rigidBody) {
		this->m_physicsBodies.erase(rigidBody);
	}

	void PhysicsSystem::free() {
		this->m_physicsBodies.clear();
	}

	void PhysicsSystem::update(t_float delta) {
		std::set<RigidBody*>::iterator it_a = this->m_physicsBodies.begin();
		std::set<RigidBody*>::iterator it_b = this->m_physicsBodies.begin();
		it_b++;
		while (it_b != this->m_physicsBodies.end()) {
			while (it_b != this->m_physicsBodies.end()) {
				this->updateBodies(*it_a, *it_b, delta);
				it_b++;
			}
			it_a++;
			it_b = it_a;
			it_b++;
		}
	}

	vec4 PhysicsSystem::getSupport(Convex* convex, Transform& transform, vec4 d) {
		t_float highest = -FLT_MAX;
		vec4 support;

		for (vec4 vertex : convex->vertices) {
			vec4 translated = transform.rotation * vertex + transform.position;
			t_float dp = dot(translated, d);
			if (dp > highest) {
				highest = dp;
				support = translated;
			}
		}
		return support;
	}

	vec4 PhysicsSystem::GJK(Convex* a, Transform& ta, Convex* b, Transform& tb) {
		Transform t_null;
		vec4 shape[4];
		int shape_it = 0;
		int ITERATIONS = 0;
		int MAX_ITERATIONS = 256;
		vec4 v = ta.rotation * *a->vertices.begin() + ta.position;// -(*b->vertices.begin() * tb.rotation + tb.position);
		bool flg = true;
		t_float epsilon = 0.01;
		while (v.length() > 0) {
			vec4 w = getSupport(a, ta, -v) - getSupport(b, tb, v);
			if (v.length() - (dot(v, w) / w.length()) < epsilon) {
				v = w;
				break;
			}
			v = w;
			if (shape_it < 4) {
				shape[shape_it] = w;
				std::cout << shape_it << " " << w.x << " " << w.y << " " << w.z << " " << w.w << std::endl;
				shape_it++;
			}
			else {
				Tetravector4 volume = (shape[0] - w) ^ (shape[1] - w) ^ (shape[2] - w) ^ (shape[3] - w);
				Tetravector4 v1 = shape[0] ^ shape[1] ^ shape[2] ^ shape[3];
				Tetravector4 v2 = shape[0] ^ shape[1] ^ shape[2] ^ w;
				Tetravector4 v3 = shape[0] ^ shape[1] ^ shape[3] ^ w;
				Tetravector4 v4 = shape[0] ^ shape[2] ^ shape[3] ^ w;
				Tetravector4 v5 = shape[1] ^ shape[2] ^ shape[4] ^ w;
				//std::cout << volume.xyzw << " " << (v1 + v2 + v3 + v4 + v5).xyzw << std::endl;
				shape_it = 0;
				ITERATIONS++;
				if (ITERATIONS > MAX_ITERATIONS) {
					break;
				}
			}
		}
		return v;
	}

	vec4 PhysicsSystem::orderedDiagonals(Convex* a, Transform& ta, Convex* b, Transform& tb) {
		StaticMesh* pb = (StaticMesh*)b->parent;
		for (vec4 i : a->vertices) {
			for (Tetrahedron t : pb->cells) {
				t.vertex = tb.rotation * t.vertex + tb.position;
				t.base_1 = tb.rotation * t.base_1 + tb.position;
				t.base_2 = tb.rotation * t.base_2 + tb.position;
				t.base_3 = tb.rotation * t.base_3 + tb.position;
				vec4 d_start = ta.position;
				vec4 d_end = ta.rotation * i + ta.position;
				vec4 volume_n = cross(t.base_1 - t.vertex, t.base_2 - t.vertex, t.base_3 - t.vertex).normalized();
				t_float d1 = dot(volume_n, d_start - t.vertex);
				t_float d2 = dot(volume_n, d_end - t.vertex);
				if ((d1 >= 0 && d2 <= 0) || (d1 <= 0 && d2 >= 0)) {
					vec4 point_in_volume = d_start + (d_end - d_start) * abs(dot(volume_n, t.vertex)) / abs(dot(volume_n, d_end - d_start));
					if (abs(dot(volume_n, t.vertex) - dot(volume_n, point_in_volume)) > 0.00000000000001) {
						continue;
					}
					//std::cout << dot(volume_n, t.vertex) - dot(volume_n, point_in_volume) << std::endl;
					//calculate volume
					Trivector4 init_volume = (t.base_1 - t.vertex) ^ (t.base_2 - t.vertex) ^ (t.base_3 - t.vertex);
					Trivector4 volume_1 = (t.vertex - point_in_volume) ^ (t.base_1 - point_in_volume) ^ (t.base_2 - point_in_volume);
					Trivector4 volume_2 = (t.vertex - point_in_volume) ^ (t.base_1 - point_in_volume) ^ (t.base_3 - point_in_volume);
					Trivector4 volume_3 = (t.vertex - point_in_volume) ^ (t.base_2 - point_in_volume) ^ (t.base_3 - point_in_volume);
					Trivector4 volume_4 = (t.base_1 - point_in_volume) ^ (t.base_2 - point_in_volume) ^ (t.base_3 - point_in_volume);
					Trivector4 volume_p = volume_1.abs() + volume_2.abs() + volume_3.abs() + volume_4.abs();
					volume_p = volume_p.abs() - init_volume.abs();
					//std::cout << volume_p.xyz << " " << volume_p.yzw << " " << volume_p.xyw << " " << volume_p.xzw << std::endl;
					if (init_volume.abs() == volume_1.abs() + volume_2.abs() + volume_3.abs() + volume_4.abs()) {
						std::cout << "collision" << std::endl;
						return point_in_volume;
					}
					//std::cout << dot(volume_n, t.vertex) - dot(volume_n, point_in_volume) << std::endl;
				}
			}
		}
		return vec4();
	}

	vec4 PhysicsSystem::volumes(Convex* a, Transform& ta, Convex* b, Transform& tb) {
		vec4 result = this->orderedDiagonals(a, ta, b, tb);
		if (result.length() > 0) {
			return result;
		}
		result = this->orderedDiagonals(b, tb, a, ta);
		return result;
	}

	void PhysicsSystem::updateBodies(RigidBody* a, RigidBody* b, t_float delta) {
		a->m_transform.position += a->m_velocity * delta;
		b->m_transform.position += b->m_velocity * delta;
		vec4 result = this->volumes(a->getConvex(), a->getTransform(), b->getConvex(), b->getTransform());
		if (result.length() > 0) {
			//a->getTransform().position += result;
			a->m_velocity *= -1;
			b->m_velocity *= -1;
		}
	}
}