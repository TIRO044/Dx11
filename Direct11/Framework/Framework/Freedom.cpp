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

		if (Keyboard::Get()->Press('E'))
		{
			p = p + right * move * Time::Delta();
		}
		else if (Keyboard::Get()->Press('Q'))
		{
			p = p - right * move * Time::Delta();
		}

		ImGui::SliderFloat3("Position", p, -100, 100);

		Position(p);
	}

	//Rotation
	{
		if (Mouse::Get()->Press(1) == false) return;

		Vector3 R;
		Rotation(&R);

		Vector3 val = Mouse::Get()->GetMoveValue();
		R.x = R.x + val.y * rotation * Time::Delta();
		R.y = R.y + val.x * rotation * Time::Delta();
		R.z = 0.0f;

		Rotation(R);
	}
}

void Freedom::Speed(float move, float rotation)
{
	this->move = move;
	this->rotation = rotation;
}
