uniform mat4 u_model;
uniform mat4 u_viewprojection;
uniform vec3 u_camera_pos;

uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;
uniform vec3 u_ambient_light;

uniform vec3 u_Ka;
uniform vec3 u_Kd;
uniform vec3 u_Ks;
uniform float u_shininess;

varying vec3 v_color;
varying vec2 v_uv;

void main()
{
    v_uv = gl_MultiTexCoord0.xy;

    //Local position to world
    vec3 world_pos = (u_model * vec4(gl_Vertex.xyz, 1.0)).xyz;
    
    //Local normal to world
    vec3 N = normalize((u_model * vec4(gl_Normal.xyz, 0.0)).xyz);

    //Vectors L, V, R
    vec3 L_vec = u_light_pos - world_pos;
    float d = length(L_vec);    //distance to light
    vec3 L = normalize(L_vec);
    vec3 V = normalize(u_camera_pos - world_pos);
    
    //Vector R
    vec3 R = reflect(-L, N);
    
    vec3 ambient = u_Ka * u_ambient_light;
    float dotLN = max(dot(L, N), 0.0);
    vec3 diffuse = dotLN * u_Kd;
    
    float dotRV = max(dot(R, V), 0.0);
    vec3 specular = pow(dotRV, u_shininess) * u_Ks;
    
    //Ip = ambient + (intensity/d^2) * (diffuse + specular)
    float attenuation = 1.0/(d*d);
    v_color = ambient + (u_light_intensity * attenuation) * (diffuse + specular);

	// Project the vertex using the model view projection matrix
	gl_Position = u_viewprojection * vec4(world_pos, 1.0); //output of the vertex shader
}
