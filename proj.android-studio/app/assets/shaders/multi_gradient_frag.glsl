varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4 u_colors[16];
uniform float u_locations[16];
uniform float u_count;
uniform vec2 u_anchorPoint;

void main() {
    int count = int(u_count);
    if (count > 1) {
        vec2 uv = v_texCoord;
        if (u_anchorPoint.x > 0.0) {
            uv.x = u_anchorPoint.x - uv.x;
        }
        if (u_anchorPoint.y > 0.0) {
            uv.y = u_anchorPoint.y - uv.y;
        }
        
        for (int i = 1; i < count; i++) {
            float p2 = u_locations[i];
            float t = (uv.x + uv.y) * 0.5;
            if (t <= p2) {
                float p1 = u_locations[i-1];

                gl_FragColor = mix(u_colors[i-1], u_colors[i], smoothstep(p1, p2, t));
                return;
            }
        }
    }
    
    gl_FragColor = u_colors[0];
}