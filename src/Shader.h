#pragma once
#include<unordered_map>
#include<string>
#include"glm/glm.hpp"
struct ShaderProgSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
	private:
		std::string m_Filepath;
		unsigned int m_RendererID;
		unsigned int GetUniformLocation(const std::string& name);
		ShaderProgSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string fragmentShader);
		std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
	public:
		Shader(const std::string& filepath);
		~Shader();
		
		void Bind() const;
		void Unbind() const;

		// Set uniforms
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

};

