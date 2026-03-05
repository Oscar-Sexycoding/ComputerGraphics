varying vec2 v_uv;
uniform int u_mode;
uniform sampler2D u_texture;

void main()
{
    vec2 uv = v_uv - 0.5;
    vec4 color = texture2D(u_texture, v_uv);
    
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
    
}
