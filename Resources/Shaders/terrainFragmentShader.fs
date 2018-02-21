precision mediump float;

varying vec2 v_uv;
varying vec2 v_uv_blend;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;

void main()
{
	vec4 vgreen =  texture2D(u_texture0, v_uv);
	vec4 vblue =   texture2D(u_texture1, v_uv);
	vec4 vrosu =   texture2D(u_texture2, v_uv);
	vec4 vblend =  texture2D(u_texture3, v_uv_blend);
	vec4 vfinal =  vblend.r * vrosu + vblend.g * vgreen + vblend.b * vblue;
	vfinal.a = 1.0;
	gl_FragColor = vfinal;
	
}