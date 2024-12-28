﻿#version 330 core

out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;   
in vec2 TexCoord;

uniform sampler2D tex0; 
uniform vec3 lightPos;  // موقع الضوء
uniform vec3 viewPos;   // موقع الكاميرا
uniform vec3 lightColor; // لون الضوء
uniform vec3 objectColor; // لون الجسم

void main()
{
    // **1. Ambient**
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // **2. Diffuse**
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // **3. Specular**
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // **4. Combine results**
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0) * texture(tex0, TexCoord);
}
