#pragma once
#include <vector>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RenderPipeline.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Mass
{
	private:
		void CalculateAcc();
		glm::vec2 m_Pos;
		glm::vec2 m_Vel;
		float m_mass;
		VertexArray m_va;
		IndexBuffer m_ib;
		Shader m_shader;
		RenderPipeline m_RP;
		const float G = 0.00000000000667f;
		glm::mat4 proj = glm::ortho(-640.f, 640.0f, -360.0f, 360.0f);
	public:
		Mass(glm::vec2 Pos, float mass, glm::vec2 vel, const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const RenderPipeline& RP);
		~Mass();
		void RenderBody();
		float GetMass() const;
		glm::vec2 GetPos() const;
		float GetDistanceSqrd(Mass* Body) const;
		float GetDisX(Mass* Body) const;
		float GetDisY(Mass* Body) const;
		static float VelocityMagNorm(glm::vec2 Speed);

		//should refactor to a hash table
		static std::vector<Mass*> Bodies;

};

