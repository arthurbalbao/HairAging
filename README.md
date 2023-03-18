<h1 align="center"><a href="https://www.inf.ufrgs.br/~mwalter/hairaging/">A Biologically Inspired Hair Aging Model</a></h1>
<p align="center">
![Teaser](./agingSimulation.gif)
  </p>
<p align="center">
	In ACM Transactions on Graphics (Proceedings of SIGGRAPH ASIA 2022)
    <br />
    <a href=""><strong>Arthur Balbao</strong></a>  <a href=https://www.inf.ufrgs.br/~mwalter/"><strong>Marcelo Walter</strong></a>
  </p>

  
  ## Overview
   This repository contains an implementation of our hair aging simulation in Unreal Engine 5. Our method was implemented as a plugin, which can be easily integrated into any Unreal project.
  
  Our system was developed and tested for MetaHumans assets, but it should work for any character with explicit hair strands.
  
      
  This repository does not include any of the MetaHuman models nor the scenes used in our paper. However, most of the characters we used are available in Quixel Bridge, as they are MetaHuman Presets provided by Epic.

 ## Installation
  To install the plugin, follow these steps:

  1. Clone this repository.
  2. Copy the plugin directory into Unreal Engine's Plugins folder, which should be located at `\Engine\Plugins`
  3. Enable the plugin in your project's Plugins settings.
      
  The current version of the plugin was built for UE 5.1.1. It may be required to rebuild it in order for it to run on newer releases of Unreal Engine. To accomplish this, take the following steps:
      
  1. Navigate inside Unreal Engine's folder.
  2. Go to `\Engine\Build\BatchFiles` 
  3. Type `RunUAT.bat BuildPlugin -plugin="PATH\TO\PLUGIN\HairAging.uplugin" -package="PATH\TO\Engine\Plugins\HairAging" -TargetPlatforms=Win64`into the CommandPrompt, replacing the respective paths. 
      
 If the build is successful, the plugin should now be updated to your UE's release version (Credit: https://dev.epicgames.com/community/learning/tutorials/0RG4/compiling-a-plugin-for-a-new-engine-version). 
      
 ## Usage
      
 The plugin is composed of three parts: a graphical interface, the hair aging materials and an aging component that is attached to each character, controlling the simulation.

 
 ### In-Editor Interface 
      
If the plugin is installed and enabled, the interface can be accessed inside Unreal Engine by clicking the `Window` tab and the `HairAging` option. 
      
The interface is where the user can set different parameters such as defining the aging rate - from early greyer to late greyer, the aging pattern - female or male, and also choose to use the default segmentation or to automatically create a new one from a normal map given as input.
         
<p align="center">  
      <img src =https://user-images.githubusercontent.com/31601033/226062798-ff9e7483-b5a2-4108-b2a4-be25beae6ee3.png >  
 </p>  
      
      
When the user selects the `Create Hair Aging Material Instance` option, an instance of the aging material will be created in the project folder, which will have the aging parameters calculated based upon the settings defined by the user. 
      
More specifically, **two** aging material instances will be created, `MI_HairAging_CharacterName` and `MI_HairAging_CharacterName_Facial`, where the first one is the material used for the character's hair, and the second one, as the name states, for facial hairs - from eyebrows to mustaches and beards. These materials will be found at `\HairAging\CharacterName\Materials\` , inside the project folder.

<p align="center">  
      <img src =https://user-images.githubusercontent.com/31601033/226065275-9df22635-424d-4d69-9224-b563af3063c0.png>
      </p>
      <p align="center">  
      Fig.1 - Example of Material Instance generated for character named Hudson.
       </p>

 If the user chooses to use a custom baked normal map to generate a more accurate segmentation, it is only required to check the `Use Custom Normal Map for Segmentation` checkbox and then to browse for the normal map. If the image is successfully selected, the new material instances generated will already account for the segmentation based upon the custom normal map. When the custom segmentation is chosen, a new texture will also be created under `\HairAging\CharacterName\Segmentation\`, which displays the resulting segmentation. 
      
 **Note**: Only *2048x2048* baked normal maps are accepted in order to avoid artifacts during the segmentation process.
     
<p align="center">  
      <img src = https://user-images.githubusercontent.com/31601033/226066721-49a16125-5a32-44b6-aeb7-4e703cd47b1e.png>
      </p>
      <p align="center">  
      Fig.2 - Example of segmentation created using a custom normal map.
       </p>
      
### Hair Aging Materials
 The main material that defines the appearance of our hair aging system is called `M_DynamicAging`. Based upon it, we derive instances for hair aging and facial hair aging.
 Each aging material instance has the following parameters and default values:
     
<p align="center">  
      <img src =https://user-images.githubusercontent.com/31601033/226068711-992c515b-4e2c-4af8-ac5e-69a946a81bb6.png>
      </p>
      <p align="center">  
      Fig.3 - Hair aging material parameters.
       </p>
 where:
      
      
- `Beta1`: variable defined in the original formulation for hair aging in our paper, influences the hair aging rate. Can be manually adjusted to allow for a faster or slower aging rate in all hairs.
- `GreyAmount`: describes the ratio Grey/White hairs, or the percentage of hairs that will turn grey instead of white.
- `GreyDesatAmount, WhiteDesatAmount`: The desaturation percentage for grey/white hairs.
- `GreyMaxMelanin, WhiteMaxMelanin` : The maximum amount of melanin a grey/white hair should have.
- `GreyMinMelanin, WhiteMinMelanin` : The minimum amount of melanin a grey/white hair should have.
- `GrowthSpeed` : describes how fast a hair shoud grow. The original value is 12 centimeters, known as the average yearly growth for a hair shaft.
- `Melanin and Redness` : The amount of melanin and redness originally present in the strands.

### Hair Aging Component

 To control the simulation aspects during runtime, it is necessary to add a Hair Aging Component to each MetaHuman Actor. This can be easily done when editing the MetaHuman Actor Blueprint, as seen below: 
      
<p align="center">  
      <img src =https://user-images.githubusercontent.com/31601033/226070633-7d997abc-b579-4f42-b0e1-b9276a211a57.png>
      </p>
      <p align="center">  
      Fig.4 - Adding an aging component.
       </p>

 Each aging component has the following parameters:
      
 - `Anim Duration`: defines, in seconds, how long the simulation should last.
 - `Init Age`: The initial age of the subject, default 20 years.
 - `Final Age`: The final age at the end of the simulation, default 100.
 - `Init Thinning`: The initial hair thickness value, default 100%, or no thinning.      
 - `Final Thinning`: The final hair thickness, default 0.4, or 60% thinning.
      
  **Note**: in order for hair thinning to function properly, the user must correctly set the hair groom that will be used inside the aging component. This can be done either in the ConstructionScript or in the EventGraph of the MetaHuman asset, as shown below:
  
<p align="center">  
      <img src =https://user-images.githubusercontent.com/31601033/226071253-0a078fb9-72c2-4e7a-b4f7-c834f63a1e48.png>
      </p>
      <p align="center">  
      Fig.5 - Setting the hair groom component.
       </p>

 ## Citation  
```bibtex
@article{10.1145/3550454.3555444,
author = {Balb\~{a}o, Arthur E. and Walter, Marcelo},
title = {A Biologically Inspired Hair Aging Model},
year = {2022},
issue_date = {December 2022},
volume = {41},
number = {6},
url = {https://doi.org/10.1145/3550454.3555444},
doi = {10.1145/3550454.3555444},
journal = {ACM Trans. Graph.},
month = {nov},
articleno = {223},
numpages = {9},
keywords = {hair rendering, hair aging, computer graphics}
}
```
      
      
