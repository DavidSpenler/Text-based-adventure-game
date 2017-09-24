#include <string>
#include <vector>
#include <map>

#include "scenario.h"
#include "action.h"

using namespace std;

vector<vector<string>> synonyms = {
	{"get","take","obtain"},
	{"look"},
	{"check","examine","inspect"},
	{"wall","walls","spikes"},
	{"talk","speak","ask"},
	{"bone","bones"},
	{"skeleton"},
	{"door","bars"},
	{"cuffs","shackles","chains"},
	{"use"},
	{"with","using","by"},
	{"stop","wedge"},
	{"break","tear","rip","slice","shear"},
	{"start","begin"},
	{"suit","suits","armour","statue","statues"},
	{"window"},
	{"knock"},
	{"open"},
	{"wear","apply"},
	{"tapestry","tapestries"},
	{"torch","torches"},
	{"rug","carpet"},
	{"treasure","treasures","gold"},
	{"sceptre"},
	{"coins"},
	{"object","objects"},
	{"game"},
	{"north"},
	{"south"},
	{"east"},
	{"west"},
	{"go","walk","travel","head"},
	{"around"},
	{"inventory","inv"},
	{"help"},
	{"monologue"},
	{"path","road","route"},
	{"castle","tower","fortress"},
	{"bushes","bush","hedge","hedges"},
	{"throne","seat"},
	{"baron","king","lord"},
	{"gardener"},
	
};

map<string,bool> conditions = {
	{"has_bone",false},
	{"used_bone",false},
	{"broke_cuffs",false},
	{"has_chamberpot",false},
	{"has_armour",false},
	{"applied_suit",false},
	{"door1_open",false},
	{"has_sceptre",false},
	{"has_coins",false},
	{"has_shovel",false},
	{"got_quest",false},
	{"has_brooch",false},
	{"has_mallet",false},
	{"has_meat",false},
	{"has_crucifix",false},
	{"has_ring",false},
	{"has_sword",false},
	{"has_torch",false},
	{"has_rope",false},
	{"has_flute",false}
};

map<string,string> inventory = {
	{"bone","The bone is very thick and stout. The creature that it belonged to must have been very formidable."},
	{"chamberpot","The pot is black and has a rounded rim."},
	{"armour","The suit consists of a chestplate, helmet, and sleeves as well as leg pieces."},
	{"sceptre","The sceptre's handle is made of solid gold and is headed by a large glistening ruby."},
	{"shovel","It is a fairly mundane shovel made of wood and metal. It seems to have been used excessively."},
	{}
};

vector<action> universal_fails = {
	action("get","Get what?"),
	action("get <any>","You can't get that."),
	action("use","Use what?"),
	action("use <any>","How would you use that?"),
	action("use <any> <any>","You can't use that on that"),
	action("talk","Talk to who?"),
	action("look","Look at what?"),
	action("help","Type commands to perform actions. For example: TALK to person, GET item, DO this WITH item, or anything else that would suit the situation. Type 'look around' to get a recap of your current surroundings. Type 'save' 1,2,3 to save your progress and 'load' 1,2,3 to load it back. Type 'quit' to exit"),
	action("<any>","That doesn't seem possible")
};

vector<scenario> scenarios = {
	scenario(
		"You find youself in a dark room, restrained by cuffs. The walls surrounding you are covered with spikes and seem to be closing in. To your left is a skeleton of some unknown creature. a door in front of you stands north",
		{
			action("look around","You find youself in a dark room, restrained by cuffs. The walls surrounding you are covered with spikes and seem to be closing in. To your left is a skeleton of some unknown creature. A door in front of you stands north.",{{}},-1,{{"used_bone",false},{"broke_cuffs",false}},{{"used_bone","You find youself in a dark room, restrained by cuffs. The walls surrounding you are covered with spikes. To your left is a skeleton of some unknown creature. A door in front of you stands north."},{"broke_cuffs","You find youself in a dark room. The walls surrounding you are covered with spikes. To your left is a skeleton of some unknown creature. A door in front of you stands north."}}),
			action("look wall","The wall is covered with very sharp spikes and draws ever nearer with each passing moment.",{{}},-1,{{"used_bone",false}},{{"used_bone","The wall is covered with spikes and is now within inches of your body."}}),			
			action("look door","The door is left ajar, as if to mock your immobility."),
			action("look cuffs","The chains that bound you are made of leather and attach to the wall behind you"),
			action("look skeleton","The skeleton is composed of very long and thick bones"),
			action("get bone *skeleton","you pry a bone from the rib-cage of the skeleton",{{"has_bone",true}},-1,{{"has_bone",false}},{{"has_bone","You see no ned to get another bone"}}),
			action("get skeleton","The skeleton is much too large to carry in its entirety"),
			action("stop wall with bone","You wait until the walls draw nearer and wedge the bone between them. The very resiliant bone keeps them from moving further",{{"used_bone",true},{"has_bone",false}},-1,{{"has_bone",true}},{{"has_bone","you don't have that."}}),
			action("use bone *stop wall","You wait until the walls draw nearer and wedge the bone between them. The very resiliant bone keeps them from moving further",{{"used_bone",true},{"has_bone",false}},-1,{{"has_bone",true}},{{"has_bone","You don't have that."}}),
			action("stop wall with <any>","You don't have that."),
			action("stop wall","How will you stop it?"),
			action("break cuffs with wall","The spikes have drawn close enough for you to brush them with your restraints. They tear with relative ease",{{"broke_cuffs",true}},-1,{{"used_bone",true}},{{"used_bone","the spikes are much too far away to make contact with. And when they draw near enough you wouldn't have the time to escape with them still closing in."}}),
			action("use wall *break cuffs","The spikes have drawn close enough for you to brush them with your restraints. They tear with relative ease",{{"broke_cuffs",true}},-1,{{"used_bone",true}},{{"used_bone","the spikes are much too far away to make contact with. And when they draw near enough you wouldn't have the time to escape with them still closing in."}}),
			action("break cuffs with bone","The bone is not sharp enough to tear the cuffs.",{{}},-1,{{"has_bone",true}},{{"has_bone","You don't have that."}}),
			action("*go north","",{},1,{{"broke_cuffs",true}},{{"broke_cuffs","Your restraints keep you from moving"}}),
			action("go (look/talk) skeleton (break/sceptre around) wall","test"),
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself in a damp stone hallway faintly illuminated by narrow windows and that runs east to west. The door to your cell lies south. You hear footsteps coming from the west"),
			action("*go south","",{{}},0,{{}},{{}}),
			action("*go west","|You run into a group of armed guards. When they see the sceptre that you are holding they immediately clear the way.",{{}},4,{{"applied_suit",true},{"has_sceptre",true}},{{"applied_suit","You run into a group of armed guards who after finding you have not met with your demise quickly impale with their spears#."},{"has_sceptre","|You run into a group of armed guards. They immediately ask where you are going and for what purpose. |Not knowing what to say, they pry the helmet from your head, revealing your identity| They impale you with their spears and leave you to die."}}),
			action("*go east","",{{}},2,{{}},{{}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You are at the end of a hallway of many beautiful tapestries, before a large oaken door, equipped with a knob and a stained-glass window. To either side of it are grand figures in suits of armour. Torches light the the vicinity, and a red rug lines the path towards it the door."),
			action("look window","You peer through the window and see two men in the same knight's uniform as in the statues outside, standing close to the other side of the door. The thickness of the glass prevents you from making out the details of anything further in the room."),
			action("look suit","The knight statues consist of a proper chestplate of iron as well as a helmat with a thick visor that practically obscures the face of the wearer."),
			action("look tapestry","The tapestries are woven with very vibrantly coloured fabrics. One such piece of art captivates your attention. It depicts a noble valiantly raising a golden sceptre to the sun, where it appears to shine light to the land beneath the noble's feet."),
			action("look torch","the torches are lit high above the opening of the door."),
			action("look rug","The rug is soft to the touch and has a deep red hue."),
			action("open door","The door is already open.",{{}},-1,{{"door1_open",true}},{{"door1_open","The door is locked"}}),
			action("knock door","You give the door a hearty thump with the brass knob. Immediately it swings open, and you are greeted by two knights. They nod to you and walk away. Perhaps they think you are here to take the next shift.",{{"door1_open",true}},-1,{{"applied_suit",true}},{{"applied_suit","You give the door a hearty thump with the brass knob. Immediately it swings open, and you are greeted by two knights. They look you up and done and immediately seize and drag you away. You do not know for sure you fate, but you fear execution will shortly follow.#"}}),
			action("get suit","You yank one of the suits from its frame. Its pieces are remarkably lighter than you had anticipated.",{{"has_armour",true}},-1,{{"has_armour",false}},{{"has_armour","You see no need to get the other suit."}}),
			action("wear suit","You sheepishly apply the chestplate sleeves, and other components to your person. At last you don the helmet, which limits your field of view quite profoundly. At any rate, the armour makes you feel less vulnerable.",{{"applied_suit",true}},-1,{{"has_armour",true}},{{"has_armour","You don't have that"}}),
			action("*go east","",{{}},3,{{"door1_open",true}},{{"door1_open","The door is locked."}}),
			action("*go west","",{{}},1,{{}},{{}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You appear to be in the treasury of the castle. You are surrounded by mounds of glimmering gold and crystal treasures."),
			action("look treasure","Gold coins scatter the room, forming a sea of large piles. Within them are assorted objects of the same lustre."),
			action("get treasure","What treasure shall you take?"),
			action("get coins","There are too many to carry in your hands, and coins are only valuable in great quantities."),
			action("get coins with chamberpot","You tuck the chamberpot under your arm and greedily toss handfuls and handfuls of coins inside.",{{"has_coins",true}},-1,{{"has_chamberpot",true}},{{"has_chamberpot","You don't have that."}}),
			action("get object","What object shall you take?"),
			action("look sceptre","The shining ruby at its head catches your eye. At first only a glimpse, you can no longer keep your eyes off it. It rests in a piles towards the corner of the room"),
			action("get sceptre","You wade your way through the sea of treasures and pluck the sceptre from its pile.",{{"has_sceptre",true}}),
			action("*go west","",{{}},2),
		}
	),
	scenario(
		"",
		{
			action("look around", "After wandering through the many halls you find yourself outside the castle. You are before many rolling hills, along which a dirt path leads. It run to the north."),
			action("look path","The path is made of dirt and gravel."),
			action("look hills","The eloquent hills are a mark of the beautiful landscape."),
			action("look castle","The castle is composed of large cobble-stone blocks, standing at least 30 meters high, with its turrets soaring to the skies. Taking note of the lack of windows, you are glad to finally be out of it."),
			action("*go south","You wish not to return to the castle whose lord imprisoned you."),
			action("*go north","|You made your way down the dirt road, still rought with fatigue and hunger from your harsh imprisonment| As you walk you take another gander at the sceptre you swindled from your incarcerator's castle. A closer inspection of it gives you a lapse of clarity as you remember why you ended up in the dungeon.| You are a travelling villein looking for work after being expelled from your fief. The baron of St. Aliquis had promised you work on his barony if you returned to him the sceptre he had lost to a feudal skirmish with the duke of Quelqueparte.| You hasten your pace as realize his hospility will soon be yours.|",{{}},5)
		}
	),
	scenario(
		"",
		{	
			action("look around","You find yourself in the  center of the bustling keep of the castle. You see many common men go about their work with much clamour and hubbub. To the north is the great donjon, to the west a group of residential buildings, to the east a marketplace, and to the south the entrance of the castle."),
			action("*go north","",{{}},6),
			action("*go south",{{}},8),
			action("*go east",{{}},9),
			action("*go west",{{}},10),
		}
	),
	scenario(
		"",
		{
			action("look around","You are before the great tower of the castle. It stands majestically above the enclosing walls of the keep. A large doors lies in front northwards, and around it are many decorative gardens of flowers and other vegetation, to which a gardener is tending. The way back is south."),
			action("look bushes","The hedges surrounding the donjon are dense both in volume and in vibrant flowers. Patterns of blue, yellow and pink dot the surface of the lush green bushes."),
			action("check bushes","You reach your hand inside the bushes, and to your wonder discover... A shovel! Seeing no one around to be using it otherwise, you decide to borrow it for the time being",{{"has_shovel",true}},-1,{{"has_shovel",false}},{{"has_shovel","You reach into the bush... and find nothing."}}),
			action("talk gardener","'I saw her rise from her grave!', he wails. 'The witch walks the earth!' You take a few steps back."),
			action("*go north","",{{}},7),
			action("*go south","",{{}},5)
		}
	),
	scenario(
		"",
		{
			action("look around","After climbing the many stairs, you find yourself in the great chamber of the baron. He sits on a throne of gold and velvet, atop a short staircase. Surrounding and illuminating the round room are many stained glass windows that stretch from the floor to the ceiling."),
			action("look *glass window","The windows depict various biblical scenes: The deception of man, the great flood, the resurrection of christ, to name a few."),
			action("look throne","The throne is made of gold and lined with purple velvet. This lord is very wealthy for the mere status of baron."),
			action("look baron","The baron sits quite non-chalantly upon the throne. He dons a modest crown of silver and three small jewels."),
			action("talk baron","|The baron sees you and in humour inquires,'Have you already recovered the sceptre of Saint. Peter?' His coyness turns to astonishment as you reveal it from your robe and present it to him|'By god, you have demonstrated diligence and compentence of enormous  proportion'. He pauses, appearing comtemplative in thought. At lasts he speaks.|'I have one final task for you, if you seek a greater reward. When I ushered you away from my estate with the impossible task of recovering my heirloom, I anticipated you'd never return. Yet you have succeeded all expectations I should have for a lowly villein.|I sense you may in fact be a man of noble blood. To prove this is so, I present to you a test feasible by a man only of the most gentle kind: Defeat the witch which has laid siege to our harvests and the wellbeing of my citizens.|If you succeed, I shall elevate your status from that of a commoner to a knight under my loyalty. Shall you accept?|You enthusiastically nod your head. He continues: 'I know little of her dwellings or her motives, but she is a practitioner of witchcraft nonetheless. You are to complete the task with your ingenuity and resourcefulness. I shall leave you with only my brooch as proof of your service to me. Now go!'",{{"got_quest",true},{"has_brooch",true},{"has_sceptre",false}},-1,{{"got_quest",false}},{{"got_quest","You ought not to return to the baron until your quest is finished."}}),
			action("*go south","",{{}},6)
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself at the outset of a chiming forest. There is a cave distantly east.")
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself at the outset of a chiming forest. There is a cave distantly east.")
		}
	)
};

int scenario_num = 0;
