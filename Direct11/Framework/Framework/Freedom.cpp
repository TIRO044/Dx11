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

	float speed = 2.0f;
	// Move
	{
		Vector3 p;
		Position(&p);

		if (Keyboard::Get()->Press('W'))
		{
			p = p + f * move * Time::Delta() * speed;
		}
		else if (Keyboard::Get()->Press('S'))
		{
			p = p - f * move * Time::Delta() * speed;
		}

		if (Keyboard::Get()->Press('D'))
		{
			p = p + u * move * Time::Delta() * speed;
		}
		else if (Keyboard::Get()->Press('A'))
		{
			p = p - u * move * Time::Delta() * speed;
		}

		if (Keyboard::Get()->Press('E'))
		{
			p = p + right * move * Time::Delta() * speed;
		}
		else if (Keyboard::Get()->Press('Q'))
		{
			p = p - right * move * Time::Delta() * speed;
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
		R.x = R.x + val.y * rotation * Time::Delta() * 0.5f;;
		R.y = R.y + val.x * rotation * Time::Delta() * 0.5f;;
		R.z = 0.0f;

		Rotation(R);
	}
}

void Freedom::Speed(float move, float rotation)
{
	this->move = move;
	this->rotation = rotation;
}
