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
        if(u_subtask == 1) color = mix(vec3(0,0,1), vec3(1,0,0), v_uv.x);
        else if(u_subtask == 2) color = vec3(distance(v_uv, vec2(0.5)));
        else if (u_subtask == 3){
            float grid = abs(sin(v_uv.x * 30.0)) + abs(sin(v_uv.y * 30.0));
            color = mix(vec3(0,0,0), vec3(1.0, 0.0, 1.0), 1.0 - grid);
        }
        else if(u_subtask == 4){
            vec3 lerp_h1 = mix(vec3(0,1,0), vec3(1,1,0), v_uv.x);
            vec3 lerp_h2 = mix(vec3(0,0,0), vec3(1,0,0), v_uv.x);
            color = mix(lerp_h2, lerp_h1, v_uv.y);
        }
    }
    
    // Fetch sampler
    vec4 texture_color = texture2D(u_texture, v_uv);
    
    // Assign the color to the pixel
    gl_FragColor = vec4(color, 1.0);
}
