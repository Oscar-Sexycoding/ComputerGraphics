varying vec2 v_uv;
uniform int u_mode;

void main()
{
    vec2 uv = v_uv - 0.5;
    
    if (u_mode == 1)
    {
        float d = distance(uv, vec2(0.0));
        float circle = step(0.25, d);
        gl_FragColor = vec4(vec3(1.0 - circle), 1.0);
    }
    else if (u_mode == 2)
    {
    }
    else if (u_mode == 3)
    {
    }
    else if (u_mode == 4)
    {
    }
    
    float d = distance(uv, vec2(0.0));
    float circle = step(0.25, d);
    gl_FragColor = vec4(vec3(1.0 - circle), 1.0);
}
