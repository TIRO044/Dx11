matrix World;
matrix View;
matrix Projection;
float3 LightDir;

struct VertexInput
{
	float4 Position : Position;
    float3 Normal : NORMAL;
};

struct VertexOutput
{
	float4 Position : SV_Position;
    float3 Normal : NORMAL;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    // 여기서 world를 float3x3하면 위치, 스케일만 남는다.
    output.Normal = mul(input.Normal, (float3x3)World);
    
	return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = input.Normal;
    float3 dir = -LightDir;
    
    return float4(1, 1, 1, 1) * dot(normal, dir);
}

RasterizerState FillMode_WireFrame
{
    FillMode = Wireframe;
};

technique11 TQ
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(FillMode_WireFrame);
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}