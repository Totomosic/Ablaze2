#include "ForwardRenderMethod.h"

namespace Ablaze
{

	void ForwardRenderMethod::Begin()
	{
	
	}

	void ForwardRenderMethod::Render(GameObject* object, GameObject* camera)
	{
		Transform& transform = object->transform();
		Mesh& mesh = object->mesh();
		Transform& cameraTransform = camera->transform();
		Camera& cameraComp = camera->GetComponent<Camera>();

		AB_INFO(object->m_Id);

		for (const ModelSet& set : mesh.GetModelSets())
		{
			const MaterialBase& mat = *set.material;
			const Resource<Model>& model = set.model;
			const Resource<Shader>& shader = mat.ActiveShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", set.transform * transform.ToMatrix());
			shader->SetUniform("viewMatrix", cameraTransform.ToMatrix().Inverse());
			shader->SetUniform("projectionMatrix", cameraComp.ProjectionMatrix());
			shader->SetUniform("color", mat.BaseColor());
			mat.Apply();
			VertexArray* vao = model->GetVertexArray();
			vao->Bind();
			glDrawElements((GLenum)vao->GetRenderMode(), vao->RenderCount(), GL_UNSIGNED_INT, nullptr);
		}
	}

	void ForwardRenderMethod::End()
	{
		
	}

	String ForwardRenderMethod::ToString() const
	{
		return "ForwardRenderMethod";
	}

}