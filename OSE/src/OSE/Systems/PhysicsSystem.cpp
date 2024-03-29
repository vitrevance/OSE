#include <OSE/Systems/PhysicsSystem.hpp>

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

void PhysicsSystem::update(float delta) {
  std::set<RigidBody*>::iterator bodyA = this->m_physicsBodies.begin();
  std::set<RigidBody*>::iterator bodyB = this->m_physicsBodies.begin();
  bodyB++;
  while (bodyB != this->m_physicsBodies.end()) {
    while (bodyB != this->m_physicsBodies.end()) {
      this->updateBodies(*bodyA, *bodyB, delta);
      bodyB++;
    }
    bodyA++;
    bodyB = bodyA;
    bodyB++;
  }
}

vec4 PhysicsSystem::getSupport(RigidBody* a, RigidBody* b, vec4 direction) {
  return a->getFurthestVertex(direction) - b->getFurthestVertex(-direction);
}

PhysicsSystem::CollisionData PhysicsSystem::calcGJK(RigidBody* rba,
                                                    RigidBody* rbb) {
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

    // OSE_LOG(LOG_OSE_TRACE, "---------------------------------");
    // OSE_LOG(LOG_OSE_TRACE, simplex.size());
    for (vec4 it : simplex) {
      // std::cout << to_str(it) << std::endl;
    }

    int scheck = this->simplexCheck(simplex, direction);
    // OSE_LOG(LOG_OSE_TRACE, "check " + std::to_string(scheck));
    if (scheck == 1) {
      // std::cout << "Collision" << std::endl;
      result.normal = calcEPA(rba, rbb, simplex);
      result.location = rba->getFurthestVertex(-result.normal);
      return result;
    } else if (scheck == -1) {
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

        float dab = dot(pab, a);
        float dac = dot(pac, a);
        float dbc = dot(pbc, b);

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

vec4 PhysicsSystem::calcEPA(RigidBody* rba, RigidBody* rbb,
                            std::vector<vec4>& simplex) {
  struct Cell {
    int a, b, c, d;
  };
  // pick any cell to begin
  std::vector<Cell> cells;
  cells.push_back({0, 1, 2, 3});
  cells.push_back({0, 1, 2, 4});
  cells.push_back({0, 1, 3, 4});
  cells.push_back({0, 2, 3, 4});
  cells.push_back({1, 2, 3, 4});

  vec4 leastNormal;

  while (true) {
    // OSE_LOG(LOG_OSE_TRACE, "CELLS " + std::to_string(cells.size()));
    int nearestCell = 0;
    float minDot = std::numeric_limits<float>::max();
    // find cell nearest to 0-coord
    for (int i = 0; i < cells.size(); i++) {
      // OSE_LOG(LOG_OSE_TRACE, "Finding nearest " + std::to_string(i));
      Cell& it = cells[i];
      vec4 a = simplex[it.a];
      vec4 b = simplex[it.b];
      vec4 c = simplex[it.c];
      vec4 d = simplex[it.d];
      // get normal for the cell
      vec4 normal = cross(b - a, c - a, d - a).normalized();
      if (dot(normal, a) < 0) {
        normal = -normal;
      }

      float dd = std::max(
          {dot(a, normal), dot(b, normal), dot(c, normal), dot(d, normal)});
      // vertices are in the same hyperplane - not a cell
      if (std::isnan(dd)) {
        // std::cout << "cc " << cells.size() << std::endl;
        // std::cout << "b " << to_str(b - a) << std::endl;
        // std::cout << "c " << to_str(c - a) << std::endl;
        // std::cout << "d " << to_str(d - a) << std::endl;
        // std::cout << ((b - a) ^ (c - a) ^ (d - a)).value() << std::endl;
        //  OSE_LOG(LOG_OSE_TRACE, "broken cell");
        continue;
      } else if (dd == 0) {
        // OSE_LOG(LOG_OSE_TRACE, "cell to cell collision");
        // is 0 in cell
        std::vector<vec4> tetra = {a, b, c, d};
        int tetraSum =
            PhysicsSystem::caseFTetrahedron(tetra, normal);  // not
                                                             // tested
      }
      // save cell nearest to 0-coord
      if (dd < minDot) {
        minDot = dd;
        nearestCell = i;
      }
    }
    // get nearest cell
    Cell& nearestIt = cells[nearestCell];
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
    // OSE_LOG(LOG_OSE_TRACE, "MinDot: " + std::to_string(minDot));
    // check if new support vector is not already a part of simplex
    bool uniq = true;
    for (vec4& vert : simplex) {
      if ((vert - support).length() == 0) {
        uniq = false;
        break;
      }
    }
    // if new support is unique and further than chosen vertex
    if (dot(support, mainNormal) > minDot && uniq) {
      simplex.push_back(support);
      int ind = simplex.size() - 1;

      cells.erase(cells.begin() + nearestCell);
      // build all possible cells with new vertex
      Cell cell1;
      cell1.a = nearestIt.a;
      cell1.b = nearestIt.b;
      cell1.c = nearestIt.c;
      cell1.d = ind;
      Cell cell2;
      cell2.a = nearestIt.a;
      cell2.b = nearestIt.b;
      cell2.c = ind;
      cell2.d = nearestIt.d;
      Cell cell3;
      cell3.a = nearestIt.a;
      cell3.b = ind;
      cell3.c = nearestIt.c;
      cell3.d = nearestIt.d;
      Cell cell4;
      cell4.a = ind;
      cell4.b = nearestIt.b;
      cell4.c = nearestIt.c;
      cell4.d = nearestIt.d;

      cells.push_back(cell1);
      cells.push_back(cell2);
      cells.push_back(cell3);
      cells.push_back(cell4);
      // erase non unique cells
      for (int i = 0; i < cells.size(); i++) {
        bool marked = false;
        Cell& c1 = cells[i];
        for (int j = i + 1; j < cells.size(); j++) {
          Cell& c2 = cells[j];
          // check if cells are not equal by calculation ind1 xor ind2 xor ...
          // == 0 if all in pairs
          if ((c1.a ^ c1.b ^ c1.c ^ c1.d ^ c2.a ^ c2.b ^ c2.c ^ c2.d) == 0) {
            marked = true;
            cells.erase(cells.begin() + j - 1);
            j--;
            // OSE_LOG(LOG_OSE_TRACE, "IF is True");
          } else {
            // OSE_LOG(LOG_OSE_TRACE, "IF is False");
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

                      if ((c1.a ^ c1.b ^ c1.c ^ c1.d ^ c2.a ^ c2.b ^ c2.c ^
      c2.d) == 0) { marked = true; new_cells.erase(new_cells.begin() + j - 1);
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
    } else {
      break;
    }
  }
  // OSE_LOG(LOG_OSE_TRACE, "Exiting EPA " + to_str(leastNormal));
  return leastNormal;
}

int PhysicsSystem::simplexCheck(std::vector<vec4>& simplex, vec4& direction) {
  switch (simplex.size()) {
    case 2:
      return this->caseLine(simplex, direction);
      break;
    case 3:
      return this->caseTriangle(simplex, direction);
      break;
    case 4:
      return this->caseFTetrahedron(simplex, direction);
      break;
    case 5:
      return this->caseFiveCell(simplex, direction);
      break;
  }
  return 0;
}

int PhysicsSystem::caseLine(std::vector<vec4>& simplex, vec4& direction) {
  vec4 a = simplex[1];
  vec4 b = simplex[0];
  vec4 ab = b - a;

  if (dot(a, b) < 0 && (a ^ b).value() < 0.0001) {
    return -1;
  }

  if (dot(ab, -a) > 0) {
    direction = -(a - (ab.normalized() * dot(a, ab.normalized()))).normalized();
  } else {
    simplex = {a};
    direction = -a.normalized();
  }
  return 0;
}

int PhysicsSystem::caseTriangle(std::vector<vec4>& simplex, vec4& direction) {
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
    return -1;  // this->Line(simplex = { b, a }, direction);
  }

  if (dot(pac, ao) > 0) {
    if (dot(ac, ao) > 0) {
      return this->caseLine(simplex = {c, a}, direction);
    } else {
      return this->caseLine(simplex = {b, a}, direction);
    }
  } else {
    if (dot(pab, ao) > 0) {
      return this->caseLine(simplex = {b, a}, direction);
    } else {
      if (abco.length() > 0) {
        if (dot(cross(abco, ac, ab), ao) > 0) {
          direction = cross(abco, ac, ab).normalized();
        } else {
          simplex = {b, c, a};
          direction = -cross(abco, ac, ab).normalized();
        }
      } else {
        return -1;
      }
    }
  }
  return 0;
}

int PhysicsSystem::caseFTetrahedron(std::vector<vec4>& simplex,
                                    vec4& direction) {
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
    return this->caseTriangle(simplex = {c, b, a}, direction);
  }
  if (dot(acd, ao) > 0) {
    return this->caseTriangle(simplex = {d, c, a}, direction);
  }
  if (dot(adb, ao) > 0) {
    return this->caseTriangle(simplex = {b, d, a}, direction);
  }

  if (abcd.length() == 0) {
    // TODO: additional check
    return 0;
  }

  if (dot(abcd, ao) > 0) {
    direction = abcd.normalized();
  } else {
    simplex = {c, d, b, a};
    direction = -abcd.normalized();
  }
  return 0;
}

int PhysicsSystem::caseFiveCell(std::vector<vec4>& simplex, vec4& direction) {
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
    // std::cout << "a" << std::endl;
    return this->caseFTetrahedron(simplex = {d, c, b, a}, direction);
  }
  if (dot(abce, ao) > 0) {
    // std::cout << "b" << std::endl;
    return this->caseFTetrahedron(simplex = {e, c, b, a}, direction);
  }
  if (dot(abde, ao) > 0) {
    // std::cout << "c" << std::endl;
    return this->caseFTetrahedron(simplex = {e, d, b, a}, direction);
  }
  if (dot(acde, ao) > 0) {
    // std::cout << "d" << std::endl;
    return this->caseFTetrahedron(simplex = {e, d, c, a}, direction);
  }
  if (dot(bcde, -b) > 0) {
    // std::cout << "e" << std::endl;
    return this->caseFTetrahedron(simplex = {e, d, c, b}, direction);
  }
  return 1;
}

void PhysicsSystem::updateBodies(RigidBody* a, RigidBody* b, float delta) {
  a->getTransform().position += a->m_velocity * delta;
  b->getTransform().position += b->m_velocity * delta;

  a->getTransform().rotation =
      Rotor4::fromMultivector(Multivector4(a->m_angVelocity * -0.5 * delta) *
                                  a->getTransform().rotation.asMultivector() +
                              a->getTransform().rotation.asMultivector());
  b->getTransform().rotation =
      Rotor4::fromMultivector(Multivector4(b->m_angVelocity * -0.5 * delta) *
                                  b->getTransform().rotation.asMultivector() +
                              b->getTransform().rotation.asMultivector());

  // a->getTransform().rotation.v2 += a->m_angVelocity * delta;
  // b->getTransform().rotation.v2 += b->m_angVelocity * delta;
  // a->m_angVelocity = a->m_angVelocity * 0.9;
  // b->m_angVelocity = b->m_angVelocity * 0.9;
  // vec4 result = this->volumes(a->getConvex(), a->getTransform(),
  // b->getConvex(), b->getTransform());
  CollisionData result = this->calcGJK(a, b);
  if (result.normal.length() > 0) {
    vec4 aVelocity = ((a->m_mass - b->m_mass) * a->m_velocity +
                      2 * b->m_mass * b->m_velocity) /
                     (a->m_mass + b->m_mass);
    vec4 bVelocity = ((b->m_mass - a->m_mass) * b->m_velocity +
                      2 * a->m_mass * a->m_velocity) /
                     (a->m_mass + b->m_mass);

    a->m_velocity =
        aVelocity;  // result.normal.normalized() * aVelocity.length();
    b->m_velocity =
        bVelocity;  //-result.normal.normalized() * bVelocity.length();

    a->m_angVelocity += ((result.location - a->getTransform().position) ^
                         result.normal.normalized()) *
                        (bVelocity.length() - aVelocity.length());
    b->m_angVelocity += ((result.location - b->getTransform().position) ^
                         result.normal.normalized()) *
                        (aVelocity.length() - bVelocity.length());
    // a->getTransform().rotation.rotate(Rotor4((result.location -
    // a->getTransform().position).normalized(), result.normal.normalized()));
    // b->getTransform().rotation.rotate(Rotor4((result.location -
    // b->getTransform().position).normalized(), result.normal.normalized()));

    // a->m_angVelocity.rotate(Rotor4((result.location -
    // a->getTransform().position).normalized(), -result.normal.normalized()));
    // b->m_angVelocity.rotate(Rotor4((result.location -
    // b->getTransform().position).normalized(), -result.normal.normalized()));

    // a->getTransform().position += result;
    // a->m_velocity *= -1;
    // b->m_velocity *= -1;
    a->getTransform().position += result.normal;
  }
}
}  // namespace OSE