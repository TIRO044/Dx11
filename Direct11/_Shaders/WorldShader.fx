matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
	float4 Position : Position;
};

struct VertexOutput
{
	float4 Position : SV_Position;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

	return output;
}

float4 PS(VertexOutput input) : SV_Target
{
	return float4(1, 0, 0, 1);
}

float4 PS2(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}

float4 PS_R(VertexOutput input) : SV_Target
{
    return float4(1, 0, 0, 1);
}

float4 PS_G(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}
float4 PS_B(VertexOutput input) : SV_Target
{
    return float4(0, 0, 1, 1);
}

RasterizerState FillMode_WireFrame
{
    FillMode = Wireframe;
};

technique11 TQ
{
	pass P0
	{
        SetRasterizerState(FillMode_WireFrame);
		SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_R()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_R()));
    }
}