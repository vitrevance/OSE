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

	vec4 PhysicsSystem::getSupport(RigidBody* a, RigidBody* b, vec4 direction) {
		return a->getFurthestVertex(direction) - b->getFurthestVertex(-direction);
	}

	PhysicsSystem::CollisionData PhysicsSystem::GJK(RigidBody* rba, RigidBody* rbb) {
		vec4 support = this->getSupport(rba, rbb, vec4(1, 0, 0, 0));
		std::vector<vec4> simplex;
		simplex.push_back(support);

		vec4 direction = -support.normalized();

		CollisionData result;

		while (true) {

			support = this->getSupport(rba, rbb, direction);

			if (dot(support, direction) <= 0) {
				return result;
			}

			simplex.push_back(support);
			
			std::cout << "---------------------------------" << std::endl;
			std::cout << simplex.size() << std::endl;
			for (vec4 it : simplex) {
				std::cout << to_str(it) << std::endl;
			}
			
			int scheck = this->SimplexCheck(simplex, direction);
			std::cout << "check " << scheck << std::endl;
			if (scheck == 1) {
				//std::cout << "Collision" << std::endl;
				result.normal = EPA(rba, rbb, simplex);
				result.location = rba->getFurthestVertex(-result.normal);
				return result;
			}
			else if (scheck == -1) {
				if (simplex.size() == 3) {
					vec4 a = simplex[2];
					vec4 b = simplex[1];
					vec4 c = simplex[0];

					vec4 ab = b - a;
					vec4 ac = c - a;
					vec4 bc = c - b;

					vec4 pab = a - (ab.normalized() * (dot(a, ab.normalized())));
					vec4 pac = a - (ac.normalized() * (dot(a, ac.normalized())));
					vec4 pbc = b - (bc.normalized() * (dot(b, bc.normalized())));
					pab.normalize();
					pac.normalize();
					pbc.normalize();

					if (dot(pab, ac) > 0) {
						pab = -pab;
					}
					if (dot(pac, ab) > 0) {
						pac = -pac;
					}
					if (dot(pbc, ab) > 0) {
						pbc = -pbc;
					}

					t_float dab = dot(pab, a);
					t_float dac = dot(pac, a);
					t_float dbc = dot(pbc, b);

					if (dab < dac && dab < dbc) {
						result.normal = pab * dab;
					}
					if (dac < dab && dac < dbc) {
						result.normal = pac * dac;
					}
					if (dbc < dab && dbc < dac) {
						result.normal = pbc * dbc;
					}
					result.location = rba->getFurthestVertex(-result.normal);
					return result;
				}
				break;
			}
		}
		return CollisionData();
	}

	vec4 PhysicsSystem::EPA(RigidBody * rba, RigidBody * rbb, std::vector<vec4>& simplex) {
		struct cell {
			int a, b, c, d;
		};

		std::vector<cell> cells;
		cells.push_back({ 0, 1, 2, 3 });
		cells.push_back({ 0, 1, 2, 4 });
		cells.push_back({ 0, 1, 3, 4 });
		cells.push_back({ 0, 2, 3, 4 });
		cells.push_back({ 1, 2, 3, 4 });

		vec4 leastNormal;

		while (true) {
			std::cout << "CELLS " << cells.size() << std::endl;
			int nearestCell = 0;
			t_float minDot = FLT_MAX;
			for (int i = 0; i < cells.size(); i++) {
				cell& it = cells[i];
				vec4 a = simplex[it.a];
				vec4 b = simplex[it.b];
				vec4 c = simplex[it.c];
				vec4 d = simplex[it.d];

				vec4 normal = cross(b - a, c - a, d - a).normalized();
				if (dot(normal, a) < 0) {
					normal = -normal;
				}

				t_float dd = std::max({ dot(a, normal), dot(b, normal), dot(c, normal), dot(d, normal) });

				if (isnan(dd)) {
					//std::cout << "cc " << cells.size() << std::endl;
					//std::cout << "b " << to_str(b - a) << std::endl;
					//std::cout << "c " << to_str(c - a) << std::endl;
					//std::cout << "d " << to_str(d - a) << std::endl;
					//std::cout << ((b - a) ^ (c - a) ^ (d - a)).value() << std::endl;
					std::cout << "broken cell" << std::endl;
					continue;
				}

				if (dd < minDot) {
					minDot = dd;
					nearestCell = i;
				}
			}

			cell nearestIt = cells[nearestCell];
			vec4 na = simplex[nearestIt.a];
			vec4 nb = simplex[nearestIt.b];
			vec4 nc = simplex[nearestIt.c];
			vec4 nd = simplex[nearestIt.d];

			vec4 mainNormal = cross(nb - na, nc - na, nd - na).normalized();
			if (dot(mainNormal, na) < 0) {
				mainNormal = -mainNormal;
			}
			vec4 support = this->getSupport(rba, rbb, mainNormal);
			leastNormal = -mainNormal * minDot;


			bool uniq = true;
			for (vec4& vert : simplex) {
				if ((vert - support).length() == 0) {
					uniq = false;
					break;
				}
			}

			if (dot(support, mainNormal) > minDot && uniq) {
				simplex.push_back(support);
				int ind = simplex.size() - 1;

				cells.erase(cells.begin() + nearestCell);

				cell cell1;
				cell1.a = nearestIt.a;
				cell1.b = nearestIt.b;
				cell1.c = nearestIt.c;
				cell1.d = ind;
				cell cell2;
				cell2.a = nearestIt.a;
				cell2.b = nearestIt.b;
				cell2.c = ind;
				cell2.d = nearestIt.d;
				cell cell3;
				cell3.a = nearestIt.a;
				cell3.b = ind;
				cell3.c = nearestIt.c;
				cell3.d = nearestIt.d;
				cell cell4;
				cell4.a = ind;
				cell4.b = nearestIt.b;
				cell4.c = nearestIt.c;
				cell4.d = nearestIt.d;

				cells.push_back(cell1);
				cells.push_back(cell2);
				cells.push_back(cell3);
				cells.push_back(cell4);

				for (int i = 0; i < cells.size(); i++) {
					bool marked = false;
					cell c1 = cells[i];
					for (int j = i + 1; j < cells.size(); j++) {
						cell c2 = cells[j];

						if ((c1.a ^ c1.b ^ c1.c ^ c1.d ^ c2.a ^ c2.b ^ c2.c ^ c2.d) == 0) {
							marked = true;
							cells.erase(cells.begin() + j - 1);
							j--;
						}
					}
					if (marked) {
						cells.erase(cells.begin() + i);
						i--;
					}
				}
				/*
				std::vector<cell> new_cells;

				for (int i = 0; i < cells.size(); i++) {
					cell it = cells[i];
					vec4 a = simplex[it.a];
					vec4 b = simplex[it.b];
					vec4 c = simplex[it.c];
					vec4 d = simplex[it.d];

					vec4 normal = cross(b - a, c - a, d - a).normalized();
					if (dot(normal, a) < 0) {
						normal = -normal;
					}

					if (dot(normal, support) >= 0) {
						cells.erase(cells.begin() + i);
						i--;

						cell cell1;
						cell1.a = it.a;
						cell1.b = it.b;
						cell1.c = it.c;
						cell1.d = ind;
						cell cell2;
						cell2.a = it.a;
						cell2.b = it.b;
						cell2.c = ind;
						cell2.d = it.d;
						cell cell3;
						cell3.a = it.a;
						cell3.b = ind;
						cell3.c = it.c;
						cell3.d = it.d;
						cell cell4;
						cell4.a = ind;
						cell4.b = it.b;
						cell4.c = it.c;
						cell4.d = it.d;

						new_cells.push_back(cell1);
						new_cells.push_back(cell2);
						new_cells.push_back(cell3);
						new_cells.push_back(cell4);
					}
				}

				for (int i = 0; i < new_cells.size(); i++) {
					bool marked = false;
					cell c1 = new_cells[i];
					for (int j = i + 1; j < new_cells.size(); j++) {
						cell c2 = new_cells[j];

						if ((c1.a ^ c1.b ^ c1.c ^ c1.d ^ c2.a ^ c2.b ^ c2.c ^ c2.d) == 0) {
							marked = true;
							new_cells.erase(new_cells.begin() + j - 1);
							j--;
						}
					}
					if (marked) {
						new_cells.erase(new_cells.begin() + i);
						i--;
					}
				}

				cells.insert(cells.end(), new_cells.begin(), new_cells.end());
				*/
			}
			else {
				break;
			}
		}
		return leastNormal;
	}

	int PhysicsSystem::SimplexCheck(std::vector<vec4>& simplex, vec4& direction) {
		switch (simplex.size()) {
		case 2:
			return this->Line(simplex, direction);
			break;
		case 3:
			return this->Triangle(simplex, direction);
			break;
		case 4:
			return this->FTetrahedron(simplex, direction);
			break;
		case 5:
			return this->FiveCell(simplex, direction);
			break;
		}
		return 0;
	}

	int PhysicsSystem::Line(std::vector<vec4>& simplex, vec4& direction) {
		vec4 a = simplex[1];
		vec4 b = simplex[0];
		vec4 ab = b - a;

		if (dot(a, b) < 0 && (a ^ b).value() < 0.0001) {
			return -1;
		}

		if (dot(ab, -a) > 0) {
			direction = -(a - (ab.normalized() * dot(a, ab.normalized()))).normalized();
		}
		else {
			simplex = { a };
			direction = -a.normalized();
		}
		return 0;
	}

	int PhysicsSystem::Triangle(std::vector<vec4>& simplex, vec4& direction) {
		vec4 a = simplex[2];
		vec4 b = simplex[1];
		vec4 c = simplex[0];

		vec4 ab = b - a;
		vec4 ac = c - a;
		vec4 ao = -a;

		vec4 pab = a - (ab.normalized() * (dot(a, ab.normalized())));
		vec4 pac = a - (ac.normalized() * (dot(a, ac.normalized())));

		if (dot(pab, ac) > 0) {
			pab = -pab;
		}
		if (dot(pac, ab) > 0) {
			pac = -pac;
		}

		vec4 abco = cross(ab, ac, ao);
		
		if ((ab ^ ac).value() == 0) {
			return -1;//this->Line(simplex = { b, a }, direction);
		}
		
		if (dot(pac, ao) > 0) {
			if (dot(ac, ao) > 0) {
				return this->Line(simplex = { c, a }, direction);
			}
			else {
				return this->Line(simplex = { b, a }, direction);
			}
		}
		else {
			if (dot(pab, ao) > 0) {
				return this->Line(simplex = { b, a }, direction);
			}
			else {
				if (abco.length() > 0) {
					if (dot(cross(abco, ac, ab), ao) > 0) {
						direction = cross(abco, ac, ab).normalized();
					}
					else {
						simplex = { b, c, a };
						direction = -cross(abco, ac, ab).normalized();
					}
				}
				else {
					return -1;
				}
			}
		}
		return 0;
	}

	int PhysicsSystem::FTetrahedron(std::vector<vec4>& simplex, vec4& direction) {
		vec4 a = simplex[3];
		vec4 b = simplex[2];
		vec4 c = simplex[1];
		vec4 d = simplex[0];

		vec4 ab = b - a;
		vec4 ac = c - a;
		vec4 ad = d - a;
		vec4 ao = -a;

		vec4 abcd = cross(ab, ac, ad);

		vec4 abc = cross(ab, ac, abcd);
		vec4 acd = cross(ac, ad, abcd);
		vec4 adb = cross(ad, ab, abcd);

		if (dot(abc, ao) > 0) {
			return this->Triangle(simplex = { c, b, a }, direction);
		}
		if (dot(acd, ao) > 0) {
			return this->Triangle(simplex = { d, c, a }, direction);
		}
		if (dot(adb, ao) > 0) {
			return this->Triangle(simplex = { b, d, a }, direction);
		}
		
		if (abcd.length() == 0) {
			std::cout << "bsdfa" << std::endl;
		}

		if (dot(abcd, ao) > 0) {
			direction = abcd.normalized();
		}
		else {
			simplex = { c, d, b, a };
			direction = -abcd.normalized();
		}
		return 0;
	}

	int PhysicsSystem::FiveCell(std::vector<vec4>& simplex, vec4& direction) {
		vec4 a = simplex[4];
		vec4 b = simplex[3];
		vec4 c = simplex[2];
		vec4 d = simplex[1];
		vec4 e = simplex[0];

		vec4 ab = b - a;
		vec4 ac = c - a;
		vec4 ad = d - a;
		vec4 ae = e - a;
		vec4 bc = c - b;
		vec4 bd = d - b;
		vec4 be = e - b;
		vec4 ao = -a;

		vec4 abcd = cross(ab, ac, ad);
		if (dot(abcd, a) < 0) {
			abcd = -abcd;
		}
		vec4 abce = cross(ab, ac, ae);
		if (dot(abce, a) < 0) {
			abce = -abce;
		}
		vec4 abde = cross(ab, ad, ae);
		if (dot(abde, a) < 0) {
			abde = -abde;
		}
		vec4 acde = cross(ac, ad, ae);
		if (dot(acde, a) < 0) {
			acde = -acde;
		}
		vec4 bcde = cross(bc, bd, be);
		if (dot(bcde, b) < 0) {
			bcde = -bcde;
		}

		if (dot(abcd, ao) > 0) {
			//std::cout << "a" << std::endl;
			return this->FTetrahedron(simplex = { d, c, b, a }, direction);
		}
		if (dot(abce, ao) > 0) {
			//std::cout << "b" << std::endl;
			return this->FTetrahedron(simplex = { e, c, b, a }, direction);
		}
		if (dot(abde, ao) > 0) {
			//std::cout << "c" << std::endl;
			return this->FTetrahedron(simplex = { e, d, b, a }, direction);
		}
		if (dot(acde, ao) > 0) {
			//std::cout << "d" << std::endl;
			return this->FTetrahedron(simplex = { e, d, c, a }, direction);
		}
		if (dot(bcde, -b) > 0) {
			//std::cout << "e" << std::endl;
			return this->FTetrahedron(simplex = { e, d, c, b }, direction);
		}
		return 1;
	}

	void PhysicsSystem::updateBodies(RigidBody* a, RigidBody* b, t_float delta) {
		a->m_transform.position += a->m_velocity * delta;
		b->m_transform.position += b->m_velocity * delta;
		//a->getTransform().rotation.v2 += a->m_angVelocity * delta;
		//b->getTransform().rotation.v2 += b->m_angVelocity * delta;
		//a->m_angVelocity = a->m_angVelocity * 0.9;
		//b->m_angVelocity = b->m_angVelocity * 0.9;
		//vec4 result = this->volumes(a->getConvex(), a->getTransform(), b->getConvex(), b->getTransform());
		CollisionData result = this->GJK(a, b);
		if (result.normal.length() > 0) {

			vec4 sum_imp = a->m_velocity * a->m_mass + b->m_velocity * b->m_mass;

			//a->m_velocity = result.normal.normalized() * sum_imp.length() / a->m_mass;
			//b->m_velocity = -result.normal.normalized() * sum_imp.length() / b->m_mass;

			//a->m_angVelocity += (result.location - a->getTransform().position) ^ result.normal;// *b->m_mass;
			//b->m_angVelocity += (result.location - b->getTransform().position) ^ result.normal;// *a->m_mass;
			//a->getTransform().rotation.rotate(Rotor4((result.location - a->getTransform().position).normalized(), result.normal.normalized()));
			//b->getTransform().rotation.rotate(Rotor4((result.location - b->getTransform().position).normalized(), result.normal.normalized()));

			//a->m_angVelocity.rotate(Rotor4((result.location - a->getTransform().position).normalized(), result.normal.normalized()));
			//b->m_angVelocity.rotate(Rotor4((result.location - b->getTransform().position), result.normal));

			//a->getTransform().position += result;
			//a->m_velocity *= -1;
			//b->m_velocity *= -1;
			a->m_transform.position += result.normal;
		}
	}
}