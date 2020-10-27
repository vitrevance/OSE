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
			vec4 translated = vertex * transform.rotation;
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
		Convex shape;
		vec4 v = *a->vertices.begin() * ta.rotation + ta.position;// -(*b->vertices.begin() * tb.rotation + tb.position);
		bool flg = true;
		t_float epsilon = 0.01;
		while (v.length() > 0) {
			vec4 w = getSupport(a, ta, -v) - getSupport(b, tb, v);
			std::cout << "dt " << v.length() - (dot(v, w) / w.length()) << std::endl;
			if (v.length() - (dot(v, w) / w.length()) < epsilon) {
				v = w;
				std::cout << "ve " << v.length() << std::endl;
				break;
			}
			v = w;
			if (shape.vertices.size() < 4) {
				shape.vertices.insert(w);
			}
			else {
				shape.vertices.insert(w);
				vec4 sup = this->getSupport(&shape, t_null, v);
			}
			std::cout << "v " << v.length() << std::endl;
		}
		return v;
	}

	vec4 PhysicsSystem::diagonals(Convex* a, Transform& ta, Convex* b, Transform& tb) {
		t_float f_sup = FLT_MAX;
		t_float dist = FLT_MAX;
		for (vec4 vert : a->vertices) {
			vec4 diagonal = vert * ta.rotation;
			vec4 sup = this->getSupport(b, tb, -diagonal);
			t_float dd = dot(ta.position - tb.position, -diagonal) / diagonal.length();
			t_float dsup = dot(sup, -diagonal) / diagonal.length() + diagonal.length();
			if ()
			
		}
		if (f_sup > dist) {
			std::cout << "overlap" << std::endl;
			return vec4();
		}
		/*
		for (vec4 vert : b->vertices) {
			vec4 diagonal = vert * tb.rotation;
			vec4 sup = this->getSupport(a, ta, -diagonal);
			if (abs(dot(sup, -diagonal)) / diagonal.length() + diagonal.length() < abs(dot(ta.position - tb.position, -diagonal))) {
				std::cout << "overlap" << std::endl;
				return vert;
			}
		}
		*/
		return vec4();
	}

	void PhysicsSystem::updateBodies(RigidBody* a, RigidBody* b, t_float delta) {
		a->m_transform.position += a->m_velocity * delta;
		b->m_transform.position += b->m_velocity * delta;
		this->diagonals(a->getConvex(), a->getTransform(), b->getConvex(), b->getTransform());
	}
}