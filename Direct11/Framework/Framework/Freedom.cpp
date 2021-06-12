#include "Framework.h"
#include "Freedom.h"

Freedom::Freedom()
{

}

Freedom::~Freedom()
{
}

void Freedom::Update()
{
	Vector3 f = Forward();
	Vector3 u = Up();
	Vector3 right = Right();

	// Move
	{
		Vector3 p;
		Position(&p);

		if (Keyboard::Get()->Press('W'))
		{
			p = p + f * move * Time::Delta();
		}
		else if (Keyboard::Get()->Press('S'))
		{
			p = p - f * move * Time::Delta();
		}

		if (Keyboard::Get()->Press('D'))
		{
			p = p + u * move * Time::Delta();
		}
		else if (Keyboard::Get()->Press('A'))
		{
			p = p - u * move * Time::Delta();
		}

		if (Keyboard::Get()->Press('Q'))
		{
			p = p + right * move * Time::Delta();
		}
		else if (Keyboard::Get()->Press('E'))
		{
			p = p - right * move * Time::Delta();
		}

		ImGui::SliderFloat3("Position", p, -100, 100);

		Position(p);
	}


	Vector3 r;
	Rotation(&r);
	/*if(Mouse::Get()->Press(1))
	{
		auto val = Mouse::Get()->GetMoveValue();
		r.x = r.x + val.y * rotation * Time::Delta();
		r.y = r.y + val.x * rotation * Time::Delta();
		r.z = 0.0f;

		ImGui::LabelText("Value X", to_string(val.x).c_str());
		ImGui::LabelText("Value Y", to_string(val.y).c_str());

		Rotation(r);
	}*/

	if (Keyboard::Get()->Press('Z'))
	{
		r.x = r.x + 0.08f * rotation * Time::Delta();
	}
	else if (Keyboard::Get()->Press('X'))
	{
		r.x = r.x - 0.08f * rotation * Time::Delta();
	}
	if (Keyboard::Get()->Press('C'))
	{
		r.y = r.y + 0.08f * rotation * Time::Delta();
	}
	else if (Keyboard::Get()->Press('V'))
	{
		r.y = r.y - 0.08f * rotation * Time::Delta();
	}
	Rotation(r);
	//ImGui::NewLine();
	//auto rx = string("Rotation x");
	//auto X = rx.append(to_string(r.x)).c_str();
	//ImGui::LabelText(X, X);
	//ImGui::NewLine();

	ImGui::NewLine();
	ImGui::LabelText("Rotation X", to_string(r.x).c_str());
	ImGui::LabelText("Rotation Y", to_string(r.y).c_str());
	ImGui::NewLine();
}

void Freedom::Speed(float move, float rotation)
{

	this->move = move;
	this->rotation = rotation;
}