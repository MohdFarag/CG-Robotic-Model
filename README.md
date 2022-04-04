# Full Robotic Body <span style="font-size:12px">with movements</span>

<b>A visualization openGl and cpp code for full robotic body model with all parts of the body, and their limitations.</b>

## Implementation details

<ul>
    <li>We completed the model of the Body and his parts by applying different transformations (Scaling, Rotation, Transformation).</li>
    <li>We animated the model by animated hands, legs, parts of them and its rotated limitations.</li>
    <li>We implement camera movements horizontally and vertically, navigate forward and backward (zoom in +, zoom out -, rotation up ↑,  rotation down ↓, rotation right →, rotation left ←) </li>
    <li>We implement the timer function to make the robot interactive without press any key.</li>
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
    <td>↑</td>
    <td>Camera rotation up</td>
    <td></td>
  </tr>
  <tr>
    <td>↓</td>
    <td>Camera rotation down</td>
    <td> </td>
  </tr>
  <tr>
    <td>→</td>
    <td>Camera rotation right</td>
    <td> </td>
  </tr>
  <tr>
    <td>←</td>
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
    <td>Space Bar</td>
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

### Seconed model (Full Body model)

<img width="400px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/prev (1).png?raw=true">

### Final model

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

<b>Camera movements:</b>

---
<img width="400px" src="https://github.com/MohdFarag/Robotic-Arm-Model/blob/main/images/cameraMovements.gif?raw=true">

## Issues we faced

<ul>
<li>Dealing with glPushMatrix and glPopMatrix functions in openGl confused us.
</li>
<span style="font-size:10px; color: green">Passed</span>
<p style="font-size:11px;">We determine the transformation functions, current matrix and stack from the first of the code to the end and solve that.</p>
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