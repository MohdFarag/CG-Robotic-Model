# CG Robotic Model

![لقطة الشاشة 2022-05-19 225553](https://user-images.githubusercontent.com/84231705/169403170-22f00223-6180-4d8a-af11-2a47116de204.png)

<b>A visualization openGl and cpp code for full robotic body model with all parts of the body, their limitations and floor and objects.</b>

## Installation
### Linux Users
`sudo apt-get install freeglut3-dev` 

### Windows Users
- Download the compiled source files <a href="https://osdn.net/projects/sfnet_colladaloader/downloads/colladaloader/colladaloader%201.1/glut-3.7.6-bin.zip/">Here</a>.
- Create a new folder in “C:\” directory, and name it “glut”.
- Inside “C:\glut”, create two new folders with names “include” and “lib”

- Create a new folder and call it “GL” inside “C:\glut\include”, copy glut.h” from the unzipped file and passed it here. where you should have : C:\glut\include\GL\glut.h

- Inside “C:\glut\lib” copy “glut.def ” + “glut32.lib” + “glut32.dll” + “README-win32.txt” from the unzipped file and passed it here. where you should have : So: C:\glut\lib\glut.def, C:\glut\lib\glut32.lib, C:\glut\lib\ glut32.dll, C:\glut\lib\ README-win32.txt

- Start, Control Panel, System, Advanced, Environment Variables

- In the “Environment Variables” window and under the “system variables” select “path”, then click “edit” and in the “variable value” label add “C:\glut\lib”, then click “Ok”

- restart your computer to make sure that the windows operating system noticed those changes.

- Go to Visual Studio and create your C++ project as follow:

    - New Project
    - Under “Installed” on the left panel; select “Visual C++”, then select “ Win32” ,select from the middle panel “Win32 console application”, rename your project (with a meaningful name, ex: HelloCG), select your path from “Browse”, then click “Ok”.
    - In the “Win32 Application Wizard” click “Next”, under “Additional options”select “Empty project”, then click “Finish”
From “Solution Explorer” window, right click on “Source Files” and chose “Add” then chose “New Item…”
    - From the “Add Existing Item” window, Add files of project.
    - Move the data&images folders to the folder of the visual studio project.
    - Go to “Project”, then “Properties” and in the “Configuration Properties” in the left panel chose “VC++ Directories”, then from the right panel edit “Include Directories” and browse to add the path of the C:\glut\include, also edit “”Library Directories” and browse to add “C:\glut\lib”.

## Implementation details

<ul>
    <li>We completed the model of the Body and his parts by applying different transformations (Scaling, Rotation, Transformation).</li>
    <li>We animated the model by animated hands, legs, parts of them and its rotated limitations.</li>
    <li>We implement camera movements horizontally and vertically, navigate forward and backward (zoom in +, zoom out -, rotation up ↑,  rotation down ↓, rotation right →, rotation left ←) </li>
    <li>We implement the timer function to make the robot interactive without press any key.</li>
    <li>Adding a floor below the robotic body.</li>
    <li>Adding a texture to the floor.</li>
    <li>Having a menu to change the texture of the floor.</li> 
    <li>Adding some objects, a scene, to the enviroment.</li>
    <li>Making an animation for the robotic body.</li>
</ul>

## Control Keys

<div class="tg-wrap"><table id="tg-fAEUi">
<thead>
  <tr>
    <th>Key</th>
    <th>Movement type</th>
    <th>Notes</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>8</td>
    <td>Camera rotation up</td>
    <td></td>
  </tr>
  <tr>
    <td>2</td>
    <td>Camera rotation down</td>
    <td> </td>
  </tr>
  <tr>
    <td>6</td>
    <td>Camera rotation right</td>
    <td> </td>
  </tr>
  <tr>
    <td>4</td>
    <td>Camera rotation left</td>
    <td> </td>
  </tr>
  <tr>
    <td>f</td>
    <td>move camera forward</td>
    <td> </td>
  </tr>
  <tr>
    <td>b</td>
    <td>move camera backward</td>
    <td> </td>
  </tr>
  <tr>
    <td>W</td>
    <td>Start/Stop animation</td>
    <td> </td>
  </tr>
  <tr>
    <td>s</td>
    <td>Shoulder Rotation</td>
    <td>Abduction</td>
  </tr>
  <tr>
    <td>S</td>
    <td>Shoulder Rotation</td>
    <td>Adduction</td>
  </tr>
  <tr>
    <td>x</td>
    <td>Right Shoulder Rotation in z-axis</td>
    <td></td>
  </tr>
  <tr>
    <td>X</td>
    <td>Right Shoulder Rotation in z-axis</td>
    <td></td>
  </tr>
  <tr>
    <td>z</td>
    <td>Left Shoulder Rotation in z-axis</td>
    <td></td>
  </tr>
  <tr>
    <td>Z</td>
    <td>Left Shoulder Rotation in z-axis</td>
    <td></td>
  </tr>
  <tr>
    <td>l</td>
    <td>Shoulders Rotation in y-axis</td>
    <td></td>
  </tr>
  <tr>
    <td>L</td>
    <td>Shoulders Rotation in y-axis</td>
    <td></td>
  </tr>
  <tr>
    <td>e</td>
    <td>elbow Rotation</td>
    <td>Flexion</td>
  </tr>
  <tr>
    <td>E</td>
    <td>elbow Rotation</td>
    <td>Extension</td>
  </tr>
  <tr>
    <td>k</td>
    <td>Knee rotation Leg1</td>
    <td>Flexion</td>
  </tr>
  <tr>
    <td>K</td>
    <td>Knee rotation Leg1</td>
    <td>Extension</td>
  </tr>
  <tr>
    <td>n</td>
    <td>Knee rotation Leg2</td>
    <td>Flexion</td>
  </tr>
  <tr>
    <td>N</td>
    <td>Knee rotation Leg2</td>
    <td>Extension</td>
  </tr>
  <tr>
    <td>h</td>
    <td>Hip rotation Leg1</td>
    <td>Abduction</td>
  </tr>
  <tr>
    <td>H</td>
    <td>Hip rotation Leg1</td>
    <td>Adduction</td>
  </tr>
  <tr>
    <td>i</td>
    <td>Hip rotation Leg2</td>
    <td>Abduction</td>
  </tr>
  <tr>
    <td>I</td>
    <td>Hip rotation Leg2</td>
    <td>Adduction</td>
  </tr>
  <tr>
    <td>o</td>
    <td>Right leg rotation</td>
    <td></td>
  </tr>
  <tr>
    <td>O</td>
    <td>Right leg rotation</td>
    <td></td>
  </tr>
  <tr>
    <td>j</td>
    <td>Left leg rotation</td>
    <td></td>
  </tr>
  <tr>
    <td>J</td>
    <td>Left leg rotation</td>
    <td></td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td></td>
  </tr>
</tbody>
</table></div>

## Preview (screenshots)

### First model  (Hand model)

<img width="200px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/img1.png?raw=true">
<img width="200px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/img2.png?raw=true">
<img width="200px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/img3.png?raw=true">

### Seconed model

<img width="410px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/prev (1).png?raw=true">
<img height="350px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/prev (2).png?raw=true">

<br>

<b>Hands movements:</b>

---
<img width="400px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/handMovements.gif?raw=true">

<br>

<b>Foot movements:</b>

---
<img width="400px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/footMovements.gif?raw=true">

<br>

<b>Camera movements & Time Function:</b>

---
<img width="400px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/cameraMovements.gif?raw=true">

### Final model


![لقطة الشاشة 2022-05-19 233919](https://user-images.githubusercontent.com/84231705/169409318-e5804486-f1a1-427f-8163-dcad7ef9d78f.png)
![image](https://user-images.githubusercontent.com/84231705/169409959-a34525ec-0db0-4931-910e-9959454cbced.png)

![bandicam 2022-05-19 23-17-03-235](https://user-images.githubusercontent.com/84231705/169406745-4d301228-818e-4fb7-a824-2a738a3edbe5.gif)
![bandicam 2022-05-19 22-36-04-460 (online-video-cutter com)](https://user-images.githubusercontent.com/84231705/169402365-cd45edb6-cdef-47bf-b6c4-7f5359cd0a40.gif)


## Issues we faced

<ul>
<li>Dealing with glPushMatrix and glPopMatrix functions in openGl confused us.
</li>
<span style="font-size:10px; color: green">Passed</span>
<li style="font-size:11px;">We determine the transformation functions, current matrix and stack from the first of the code to the end and solve that.</li>
<li>The process of placing the objects in their location and maintainng the transformation was challenging and time consuming.</li>
<li>The Animation that is added to the robot was very hard as we tried to make it look as real as possible.</li>
</ul>

---

## ✨ Contributors

<span>
<img style="width:50px; height=50px" src="https://user-images.githubusercontent.com/84231705/157937789-63dbdc00-fe72-4536-b094-6b2502ac228b.png"/>
<a href="https://github.com/MohdFarag">Mohamed Ahmed</a>
</span>
<br>
<span>
<img style="width:50px; height=50px" src="https://user-images.githubusercontent.com/84231705/157937747-2c4551ab-01ef-4ff6-827b-73bf0ead28db.png"/>
<a href="https://github.com/Ismail-Tawfik">Ismail Tawfik</a>
</span>

---

### Note: Source of starter code: <a href="https://github.com/sbme-tutorials/Computer-Graphics-Tutorials/blob/master/Tutorial-02/arm.c">source</a>

thanks!
