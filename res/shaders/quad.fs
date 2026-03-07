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
            float frequency = 15.0;
            float red_pulse = pow(abs(sin(v_uv.x * frequency)), 5.0);
            float blue_pulse = pow(abs(sin(v_uv.y * frequency)), 5.0);

            //Combine pulses
            color = vec3(red_pulse, 0.0, blue_pulse);
        }
        else if(u_subtask == 4){
            vec2 square = floor(v_uv * 20.0) / 20.0;
            vec3 lerp_h1 = mix(vec3(0,1,0), vec3(1,1,0), square.x);
            vec3 lerp_h2 = mix(vec3(0,0,0), vec3(1,0,0), square.x);
            color = mix(lerp_h2, lerp_h1, square.y);
        }
        else if(u_subtask == 5){
            vec2 square = floor(v_uv * 20.0);
            float m = mod(square.x + square.y, 2.0);
            color = vec3(m);
        }
        else if(u_subtask == 6){
            //float s = sin(v_uv.x);
            float s = 0.5 + 0.25*sin(v_uv.x*6.28);
            float below = step(v_uv.y, s);
            float above = step(s, v_uv.y);
            vec3 lerp_above = mix(vec3(0, above, 0), vec3(0, above - 1.0, 0), v_uv.y);
            vec3 lerp_below = mix(vec3(0, below - 1.0, 0), vec3(0, below, 0), v_uv.y);
            //color = mix(lerp_above, lerp_below, v_uv.y);   //Make it darker
            //color = lerp_above;
            color = lerp_above * above + lerp_below * below;
            
            
        }
    }
    
    // Fetch sampler
    vec4 texture_color = texture2D(u_texture, v_uv);
    
    // Assign the color to the pixel
    gl_FragColor = vec4(color, 1.0);
}
