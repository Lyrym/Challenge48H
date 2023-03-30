# The Probably Enchanted Cavern -- UnrealEngine5 - 2023: 
Game made during 2022/2023 year for a game jam at Ynov Bordeaux.

Developer team :

- [Léo Séry](https://github.com/LeoSery)
- [Lucas Milh](https://github.com/Okaeri-nasaii)
- [Titouan Mathis](https://github.com/Lyrym)

Artist team :

- [Arthur Fernandez](https://www.artstation.com/arthurfernandez3d1)
- [Léa Signoret](https://www.artstation.com/leacide)
- [Mathis Desage](https://www.artstation.com/mathis_desage16)
- [Andréa Marignale](https://www.artstation.com/arthurfernandez3d1)

![](https://i.imgur.com/v1VrlOS.jpg)

![](https://i.imgur.com/CZqXuBS.jpg)

## Summary :

- Presentation
- Game keys
- Main mechanics
- How to open the project
- How to build the project

## Presentation :

You play as a spirit named Goutie whose goal is to cross an ***[probably] enchanted cave***.

To help her in her quest, she will be able to use different **power orbs**: the ***Fire***, ***Ice*** and ***Poison*** orb. Each of these orbs gives her a specific power to continue progressing through the level.

But be careful, each power **orb brings its counterpart**. Make the best use of the available powers to reach the end of the level as quickly as possible.

**Find the power orbs** to **acquire new skills** and allow Goutie to overcome the obstacles to reach the end of the level.

## Game keys :

- *Movement*:
    - Move to the left: **Q**
    - Move to the right: **D**
    - Jump **Space and Z**

- *Objects*:
    -  Pick : **E**

- *Use power-ups*:
    - Fire : **I**
    - Ice : **O**
    - Poison : **P**

## Main mechanics : 

### Orbs of Fire 🔥:

The orb of fire allows goutie to accelerate. Use this orb to gain speed and pass certain obstacles.

#### **Powers of the orb :**

- Positive : Gives an acceleration to Goutie.
- Negative : Goutie can't stop while this power is active.

### Orbs of Ice 🧊:

The Ice Orb allows Goutie not to slide on the ice platforms. Use this orb to climb ice slopes without slipping.

#### **Powers of the orb :**

- Positive: Allows Goutie to not slip on the ice.
- Negative : Goutie starts to slide on the stone platforms.

### Orbs of Poison 🧪:

The Poison orb allows goutie to have a double jump. Use this orb to jump over obstacles that are normally too high or too far away.

#### **Powers of the orb :**

- Positive : Allows Goutie to jump twice.
- Negative : Reverse the commands during the duration of the power.

## How to open the project:

- Clone the git repository to your computer with the following command :
```
git@github.com:Lyrym/Challenge48H.git
```
or 
```
https://github.com/Lyrym/Challenge48H.git
```

- Open the project folder and right click on `Challenge48H.uproject`

    - Select "`Generate Visual Studio Project Files`"
    - Launch `Challenge48H.uproject`
    - Click **yes** to rebuild

Note: If this doesn't work you will need the Framework SDK version to be superior than 4.6.0
    
    

- Check that your Unreal Engine version is "**5.1.1**"

## How to build the project : 

- Once the project is open in Unreal, do *"Platform" > "Windows" > "Package Project"*

- Select an installation folder and wait for the end of the build.
