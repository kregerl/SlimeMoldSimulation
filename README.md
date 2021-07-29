# Slime Mold Simulation

This is a simulaton of a slime mold written in C++ implemented as an OpenGL compute shader.  
![img.png](images/img.png)
The simulation has a few basic controls that can be manipulated at runtime:

- ### Settings:
    - Color: The main color of agents in the simulation.
    - #### Effect Settings:
        - Blur: Enables or disables blurring.
        - Diffuse Speed: How fast the agent's trails will diffuse.
        - Evaporate Speed: How fast the agent's trails will evaporate.
        - Color Mod: This a modification to the resulting color after the applying the effects. This color is subtracted
          from the diffused and evaporated value.  
          Ex: A color mod of (R:0.0, G:0.0, B:1.0) will remove all blue from the resulting blur.
    - #### Agent Settings:
        - Speed: How fast the agents are able to move.
        - Turn Speed: How fast the agents are able to turn towards another. This is only applied to the agents angle and
          does not affect their overall speed.
        - Sensor Offset Distance: How far away each agent will look for other agents.
        - Sensor Angle Offset: An offset to the agent's current angle, determines the angle that agents can sense each
          other at.
        - Sensor Size: The distance in which an agent can sense another in every direction.

### More Images

---

![img_1.png](images/img_1.png)

![img_2.png](images/img_2.png)

---

### Real Slime Mold

![Slime Mold](https://dwgyu36up6iuz.cloudfront.net/heru80fdn/image/upload/c_fill,d_placeholder_wired.png,fl_progressive,g_face,h_450,q_80,w_800/v1572020742/wired_mycologist-explains-how-a-slime-mold-can-solve-mazes.jpg)

### Future Plans

I plan on implementing a play / pause and reset button, although that can be done using the agent speed slider it'll be
a small quality of life change.  
I would like to add brushes that allow the user to create new agents using the mouse. When the mouse is clicked and the
simulation is running I would like to push the agents away from the mouse.  
Species: Inspired from [Sebastian Lague's video](https://www.youtube.com/watch?v=X-iSQQgOd1A) I would also like to add
species, where different species can be controlled individually in the settings.