varying vec2 v_uv;
varying vec3 v_world_pos;
varying vec3 v_world_normal;

uniform mat4 u_model;

uniform vec3 u_camera_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;
uniform vec3 u_ambient_light;

uniform vec3 u_Ka;
uniform vec3 u_Kd;
uniform vec3 u_Ks;
uniform float u_shininess;

uniform bool u_show_color_texture;
uniform bool u_show_specular_texture;
uniform bool u_show_normal_texture;

uniform sampler2D u_color_texture;
uniform sampler2D u_normal_texture;

void main()
{
    vec3 Ka = u_Ka;
    vec3 Kd = u_Kd;
    vec3 Ks = u_Ks;
    vec3 N;
    
    if(u_show_color_texture){
        vec4 tex_color = texture2D(u_color_texture, v_uv);
        
        Ka = tex_color.rgb;
        Kd = tex_color.rgb;
        
        if(u_show_specular_texture) {
            Ks = vec3(tex_color.a);
        }
    }
    
    if(u_show_normal_texture){
        vec3 normal = texture2D(u_normal_texture, v_uv).xyz;
        
        //Local to world
        vec3 local_normal = normalize(normal * 2.0 - 1.0);
        
        //Smooth edges (note)
        vec3 world_n_map = (u_model * vec4(local_normal, 0.0)).xyz;
        
        N = normalize(mix(normalize(v_world_normal), world_n_map, 0.6));
    }
    else {
        N = normalize(v_world_normal);
    }
    
    //Vectors L, V, R
    vec3 L_vec = u_light_pos - v_world_pos;
    float d = length(L_vec);
    vec3 L = normalize(L_vec);
    vec3 V = normalize(u_camera_pos - v_world_pos);
    vec3 R = reflect(-L, N);

    vec3 ambient = Ka * u_ambient_light;
    
    float dotLN = max(dot(L, N), 0.0);
    vec3 diffuse = dotLN * Kd;

    float dotRV = max(dot(R, V), 0.0);
    vec3 specular = pow(dotRV, u_shininess) * Ks;

    float attenuation = 1.0 / (d * d);
    vec3 final_lighting = ambient + (u_light_intensity * attenuation) * (diffuse + specular);
    
    gl_FragColor = vec4(final_lighting, 1.0);
}
