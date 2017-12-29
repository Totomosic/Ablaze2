#include "ForwardRenderMethod.h"

namespace Ablaze
{

	void ForwardRenderMethod::Begin()
	{
	
	}

	void ForwardRenderMethod::Render(GameObject* object, GameObject* camera)
	{
		Transform& transform = object->transform();
		MeshRenderer& mesh = object->mesh();
		Transform& cameraTransform = camera->transform();
		Camera& cameraComp = camera->GetComponent<Camera>();

		for (int i = 0; i < mesh.MeshCount(); i++)
		{
			MeshSet& set = mesh.GetMeshSet(i);
			Model* model = set.mesh->GetModel();
			VertexArray* vao = model->GetVertexArray();
			for (int j = 0; j < model->SubModelCount(); j++)
			{
				Material* mat = model->GetSubModel(i)->GetMaterial();
				if (mat == nullptr)
				{
					mat = set.mesh->GetDefaultMaterial();
				}
				Shader* shader = mat->ActiveShader();
				shader->Bind();
				shader->SetUniform("modelMatrix", transform.ToMatrix() * set.transform);
				shader->SetUniform("viewMatrix", cameraTransform.ToMatrix().Inverse());
				shader->SetUniform("projectionMatrix", cameraComp.ProjectionMatrix());
				shader->SetUniform("color", mat->BaseColor());
				mat->Apply();
				vao->SetCurrentIndexBuffer(j);
				vao->Bind();
				GL_CALL(glDrawElements((GLenum)vao->GetRenderMode(), vao->RenderCount(), (GLenum)vao->GetIndexBuffer(j)->DataType(), nullptr));
			}
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