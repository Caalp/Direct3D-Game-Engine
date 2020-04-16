cbuffer CBuf
{
    float4 face_colors[8];
};

float4 main() : SV_Target
{
    //return face_colors[(tid / 2) % 8];
    return float4(0.2f, 0.5f, 0.6f, 1.0f);
    
}