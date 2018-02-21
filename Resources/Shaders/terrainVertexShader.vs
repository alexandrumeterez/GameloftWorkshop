attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv_blend;

uniform mat4 u_matrix;
uniform vec3 u_height;
uniform sampler2D u_texture3;

varying vec2 v_uv;
varying vec2 v_uv_blend;

void main()
{
	vec3 pos_nou = a_posL; 

	vec4 vblend =  texture2D(u_texture3, a_uv_blend);

	pos_nou.y += vblend.r * u_height.r + vblend.g * u_height.g + vblend.b * u_height.b;

	gl_Position = u_matrix * vec4(pos_nou, 1.0);

	v_uv_blend = a_uv_blend;
	v_uv = a_uv;
}