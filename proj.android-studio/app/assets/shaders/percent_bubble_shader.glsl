varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float u_percent;

void main()
{
    if (v_texCoord.y > u_percent + 0.08) {
        discard;
    }
    
    float dist = distance(v_texCoord, vec2(0.5, 0.5));
    if (dist > 0.42) {
        discard;
    }
    
    gl_FragColor = v_fragmentColor;
}
