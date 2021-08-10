matrix World;
matrix View;
matrix Projection;
TextureCube SkyCubeMap;

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 oPosition : Position1;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.oPosition = input.Position.xyz;
    
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Normal = mul(input.Normal, (float3x3) World);
    
    output.Uv = input.Uv;

    return output;
}

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;

    AddressU = Wrap;
    AddressV = Wrap;
};

float4 PS(VertexOutput input) : SV_Target
{
    return SkyCubeMap.Sample(LinearSampler, input.oPosition);
}

// 반 시계 방향으로 돌려줘야 함
RasterizerState FrontCounterClockWiseState_True
{
    FrontCounterClockWise = True;
};

DepthStencilState DepthEnable_False
{
    DepthEnable = false;
};

// 그리고 뎁스를 지워주면 됨

technique11 T0
{
    pass P0
    {
        SetRasterizerState(FrontCounterClockWiseState_True);
        SetDepthStencilState(DepthEnable_False, 0);
        
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}