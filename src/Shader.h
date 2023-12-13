#pragma once

#include <string>

#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_VertexFilePath;
	std::string m_FragmentFilePath;
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	~Shader();

	void Bind() const;
	static void Unbind();

	//Set uniforms
	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

private:
	std::string ReadShaderFile(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	unsigned int GetUniformLocation(const std::string& name) const;


};
