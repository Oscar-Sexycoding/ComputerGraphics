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
            // 1. Set the frequency (how many lines)
            float frequency = 15.0;

            // 2. Vertical Lines (Red Channel)
            // We use abs(sin()) to get a repeating 0-to-1-to-0 pulse.
            // We use pow() to make the lines thinner and the black areas wider.
            float red_pulse = pow(abs(sin(v_uv.x * frequency)), 5.0);
            
            // 3. Horizontal Lines (Blue Channel)
            // Same logic, but using the Y coordinate.
            float blue_pulse = pow(abs(sin(v_uv.y * frequency)), 5.0);

            // 4. Combine them
            // R = red_pulse, G = 0, B = blue_pulse
            // Where they overlap, it naturally becomes Pink (1, 0, 1)
            color = vec3(red_pulse, 0.0, blue_pulse);
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
