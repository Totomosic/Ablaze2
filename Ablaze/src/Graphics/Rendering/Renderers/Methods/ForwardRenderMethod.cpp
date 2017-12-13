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

		for (int i = 0; i < mesh.ModelCount(); i++)
		{
			ModelSet& set = mesh.GetModelSet(i);
			MaterialBase* mat = set.material.get();
			std::shared_ptr<Model>& model = set.model;
			std::shared_ptr<Shader>& shader = mat->ActiveShader();
			shader->Bind();
			shader->SetUniform("modelMatrix", transform.ToMatrix() * set.transform);
			shader->SetUniform("viewMatrix", cameraTransform.ToMatrix().Inverse());
			shader->SetUniform("projectionMatrix", cameraComp.ProjectionMatrix());
			shader->SetUniform("color", mat->BaseColor());
			mat->Apply();
			VertexArray* vao = model->GetVertexArray();
			vao->Bind();
			GL_CALL(glDrawElements((GLenum)vao->GetRenderMode(), vao->RenderCount(), GL_UNSIGNED_INT, nullptr));
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