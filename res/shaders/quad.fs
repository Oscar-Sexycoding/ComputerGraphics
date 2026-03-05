varying vec2 v_uv;

uniform int u_task;
uniform int u_subtask;
uniform float u_aspect;

// Receive the texture as a sampler2D from our application
uniform sampler2D u_texture;

void main()
{
    vec3 color = vec3(0.0);
    vec2 uv_aspect = vec2(v_uv.x * u_aspect, v_uv.y);
    
    if (u_task == 1){
        switch(u_task){
            case 1: color = mix(vec3(0,0,1), vec3(1,0,0), v_uv.x); break;
            case 2: color = vec3(distance(v_uv, vec2(0.5)));
            case 3:
                float grid = abs(sin(v_uv.x * 30.0)) + abs(sin(v_uv.y * 30.0));
                color = mix(vec3(0,0,0), vec3(1.0, 0.0, 1.0), 1.0 - grid);
            case 4:
                
        }
    }
    // Fetch sampler
    vec4 texture_color = texture2D(u_texture, v_uv);

    if (
    
    // Assign the color to the pixel
    gl_FragColor = color;
}
