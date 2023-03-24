#include "Mass.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

std::vector<Mass*> Mass::Bodies = {};

void Mass::CalculateAcc()
{
	glm::vec2 Acc(0,0);
	for (unsigned int i = 0; i < Bodies.size(); i++)
	{ 
		if (Bodies[i] == this) {
			continue;
		}

		float DisX = GetDisX(Bodies[i]);
		float DisY = GetDisY(Bodies[i]);

		float NetAcc = (G * Bodies[i]->GetMass() *10000000) / (GetDistanceSqrd(Bodies[i]));

		Acc.x += NetAcc * (DisX);
		Acc.y += NetAcc * (DisY);
	}

	m_Vel.x += Acc.x;
	m_Vel.y += Acc.y;

	m_Pos.x += m_Vel.x;
	m_Pos.y += m_Vel.y;
}

Mass::Mass(glm::vec2 Pos, float mass, glm::vec2 vel, const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const RenderPipeline& RP)
	:m_va(va), m_ib(ib), m_shader(shader), m_RP(RP), m_Pos(Pos), m_mass(mass), m_Vel(vel)
{
	Bodies.push_back(this);
}

Mass::~Mass()
{
}

void Mass::RenderBody()
{
	CalculateAcc();

	if (abs(m_Pos.x) > 1000 || abs(m_Pos.y) > 1000)
	{
		Bodies.erase(std::remove(Bodies.begin(), Bodies.end(), this), Bodies.end());
		return;
	}

	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0.0f));
	glm::mat4 mvp = proj * view;
	m_shader.SetUniformMat4f("u_MVP", mvp);
	m_RP.Draw(m_va, m_ib, m_shader);
}

float Mass::GetMass()const
{
	return m_mass;
}

glm::vec2 Mass::GetPos() const
{
	return m_Pos;
}


float Mass::GetDisX(Mass* Body) const {
	float DisX = Body->GetPos().x - m_Pos.x;
	if (DisX <= 1 && DisX >= 0) {
		DisX = 1;
	}
	else if (DisX >= -1 && DisX <= 0) {
		DisX = -1;
	}
	return DisX;
}

float Mass::GetDisY(Mass* Body) const {
	float DisY = Body->GetPos().y - m_Pos.y;
	if (DisY <= 1 &&  DisY >= 0) {
		DisY = 1;
	}
	else if (DisY >= -1 && DisY <= 0) {
		DisY = -1;
	}
	return DisY;
}


float Mass::GetDistanceSqrd(Mass* Body) const
{
	float DisX = GetDisX(Body);
	float DisY = GetDisY(Body);
	return (
			abs(DisX * DisX * DisX) + abs(DisY * DisY * DisY)
		);
}