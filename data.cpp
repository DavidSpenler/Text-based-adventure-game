#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "scenario.h"
#include "action.h"

using namespace std;

vector<vector<string>> synonyms = {
	{"restart"},
	{"load"},
	{"save"},
	{"get","take","obtain"},
	{"look"},
	{"check","examine","inspect"},
	{"wall","walls","spikes"},
	{"talk","speak","ask"},
	{"bone","bones"},
	{"skeleton"},
	{"chamberpot","chamber"},
	{"door","bars"},
	{"cuffs","shackles","chains"},
	{"use"},
	{"with","using","by"},
	{"stop","wedge"},
	{"break","tear","rip","slice","shear"},
	{"start","begin","make","build"},
	{"suit","suits","armour","statue","statues"},
	{"window"},
	{"glass"},
	{"knock"},
	{"open"},
	{"wear","apply"},
	{"tapestry","tapestries"},
	{"torch","torches"},
	{"rug","carpet"},
	{"treasure","treasures"},
	{"gold"},
	{"silver"},
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
	{"clocktower"},
	{"bushes","bush","hedge","hedges"},
	{"throne","seat"},
	{"baron","king","lord"},
	{"gardener"},
	{"flip","turn","pull","flick"},
	{"lever","switch"},
	{"lantern","candle"},
	{"hole"},
	{"grave","graves"},
	{"tombstone","tomb"},
	{"abbey","church"},
	{"tree"},
	{"climb","ascend"},
	{"descend","down"},
	{"tie","wrap"},
	{"house","houses"},
	{"dig"},
	{"gravekeeper","gravekeep"},
	{"give"},
	{"shovel"},
	{"desk"},
	{"drawer","drawers"},
	{"note","notes","diary","sign"},
	{"bed","mattress"},
	{"under","beneath"},
	{"man","guard","knight"},
	{"stones","stone","rocks","rock","pebbles"},
	{"throw","chuck"},
	{"clock","face"},
	{"key"},
	{"unlock"},
	{"read"},
	{"kill","murder","slash","stab"},
	{"sword","dagger"},
	{"jehovah","Jehovah"},
	{"cut"},
	{"gears","gear"},
	{"brooch","badge"},
	{"say","speak","yell"},
	{"coffin"},
	{"shop"},
	{"cabin","shed"},
	{"body"},
	{"rope"},
	{"camp","encampment"},
	{"fire","fireplace"},
	{"hammer"},
	{"mallet"},
	{"map"},
	{"show"},
	{"skull"},
	{"lock"},
	{"smash","hit"},
	{"seeds","bag","seed"},
	{"francs","franc","money"},
	{"chest","trunk"},
	{"flint"},
	{"and"},
	{"steel"},
	{"light","burn"},
	{"wand"},
	{"witch"},
	{"mailbox","mail"},
	{"stump"},
	{"chandelier"},
	{"crown"},
	{"jewel"},
	{"words","word"},
	{"shopkeeper","shopkeep","merchant"}
};

map<string,bool> conditions = {
	{},
	{"has_bone",false},
	{"used_bone",false},
	{"broke_cuffs",false},
	{"has_chamberpot",false},
	{"has_armour",false},
	{"applied_suit",false},
	{"opened_door1",false},
	{"has_sceptre",false},
	{"has_coins",false},
	{"has_shovel",false},
	{"got_quest",false},
	{"has_brooch",false},
	{"has_lantern",false},
	{"lit_lantern",false},
	{"tied_rope",false},
	{"in_tree",false},
	{"has_mallet",false},
	{"has_meat",false},
	{"has_crucifix",false},
	{"has_ring",false},
	{"has_sword",false},
	{"has_torch",false},
	{"has_rope",false},
	{"has_flute",false},
	{"gave_shovel",false},
	{"has_stones",false},
	{"threw_stones",false},
	{"fixed_clock",false},
	{"has_skull_key",false},
	{"has_gold_key",false},
	{"has_silver_key",false},
	{"has_map",false},
	{"killed_man",false},
	{"said_words",false},
	{"read_name",false},
	{"broke_lock",false},
	{"has_francs",false},
	{"has_seeds",false},
	{"has_crown",false},
	{"gave_seeds",false},
	{"has_flint_and_steel",false},
	{"started_fire",false},
	{"opened_door2",false},
	{"opened_door3",false},
	{"opened_door4",false},
	{"has_wand",false},
	{"killed_witch",false},
	{"has_jewel",false}
};

map<string,string> inventory = {
	{"bone","The bone is very thick and stout. The creature that it belonged to must have been very formidable."},
	{"chamberpot","The pot is black and has a rounded rim."},
	{"armour","The suit consists of a chestplate, helmet, and sleeves as well as leg pieces."},
	{"sceptre","The sceptre's handle is made of solid gold and is headed by a large glistening ruby."},
	{"brooch","The brooch consists of a red crystal surrounded by beads of gold"},
	{"shovel","It is a fairly mundane shovel made of wood and metal. It seems to have been used excessively."},
	{"lantern","The lantern is made of a cheap metal, as evidenced by its many dents. Inside the cage is a small wax candle"},
	{"rope","The rope is reasonably thick and stretches about 5 meters"},
	{"stones","You have a small collection of smooth stones, ranging in colour from light grey to a pale, earthy red"},
	{"crown","The crown is made of a firm gold and illuminates itself with many deeply coloured crystals"},
	{"jewel","The jewel has a deep red hue, and glistens in sunlight. To stare into it is mesmerizing, as if a portal to a sed of red"},
	{"gold_key","The key is a glimmering gold colour"},
	{"silver_key","The key has a tainted silver complexion"},
	{"skull_key","The decaying key is headed by a skull, and it appears as though the arm is also composed of bone"},
	{"map","The map describes the paths and routes of the forest south of the castle"},
	{"seeds","The seeds have very vibrant colours"},
	{"francs","The legal tender are small coins with thick rims, and a dirty tael hue You have about thirty in total"},
	{"sword","The sword has a tough iron hilt. The blade is long and tapers smoothly into a sharp point. In the center is a green jewel, encased in which is a sliver of Christ's cross"},
	{"flint_and_steel","The set is withered and rough, but it should still do the job nonetheless."},
	{"wand","The wand is frail and tattered. But you feel an aura of evil as you clutch it in your hands"}
};


vector<action> universal_fails = {
	action("get","Get what?"),
	action("get <any>","You can't get that."),
	action("use","Use what?"),
	action("use <any>","How would you use that?"),
	action("use <any> <any>","You can't use that on that"),
	action("give","Give what?"),
	action("give <any>","Who will you give it to?"),
	action("give <any> <any>","You can't give that"),
	action("talk","Talk to who?"),
	action("talk <any>","He isn't here"),
	action("look","Look at what?"),
	action("help","Type commands to perform actions. For example: TALK to person, GET item, DO this WITH item, or anything else that would suit the situation. Type 'look around' to get a recap of your current surroundings. Type 'save' 1,2,3 to save your progress and 'load' 1,2,3 to load it back. Type 'quit' to exit"),
	action("<any>","That doesn't seem possible"),
	action("light lantern","How will you light it?",{{}},-1,{{"has_lantern",true}},{{"has_lantern","You don't have that"}})
};

vector<scenario> scenarios = {
	scenario(
		"You find youself in a dark room, restrained by cuffs. The walls surrounding you are covered with spikes and seem to be closing in. To your left is a skeleton of some unknown creature. a door in front of you stands north A chamber pot lies beside it",
		{
			action("look around","You find youself in a dark room, restrained by cuffs. The walls surrounding you are covered with spikes and seem to be closing in. To your left is a skeleton of some unknown creature. A door in front of you stands north. A chamber pot lies beside it",{{}},-1,{{"used_bone",false},{"broke_cuffs",false}},{{"used_bone","You find youself in a dark room, restrained by cuffs. The walls surrounding you are covered with spikes. To your left is a skeleton of some unknown creature. A door in front of you stands north. A chamber pot lies beside it"},{"broke_cuffs","You find youself in a dark room. The walls surrounding you are covered with spikes. To your left is a skeleton of some unknown creature. A door in front of you stands north. A chamber pot lies beside it"}}),
			action("look wall","The wall is covered with very sharp spikes and draws ever nearer with each passing moment.",{{}},-1,{{"used_bone",false}},{{"used_bone","The wall is covered with spikes and is now within inches of your body."}}),			
			action("look door","The door is left ajar, as if to mock your immobility."),
			action("look cuffs","The chains that bound you are made of leather and attach to the wall behind you"),
			action("look skeleton","The skeleton is composed of very long and thick bones"),
			action("look chamberpot","The chamberpot is dark and round, with a prominent lip."),
			action("get bone *skeleton","you pry a bone from the rib-cage of the skeleton",{{"has_bone",true}},-1,{{"has_bone",false}},{{"has_bone","You see no need to get another bone"}},1),
			action("get chamberpot","You grab the chamber pot. Luckily, it's empty.",{{"has_chamberpot",true}},-1,{{"has_chamberpot",false},{"broke_cuffs",true}},{{"has_chamberpot","You already have that."},{"broke_cuffs","The pot is just out of reach"}},1),
			action("get skeleton","The skeleton is much too large to carry in its entirety"),
			action("stop wall with bone","You wait until the walls draw nearer and wedge the bone between them. The very resiliant bone keeps them from moving further",{{"used_bone",true},{"has_bone",false}},-1,{{"has_bone",true}},{{"has_bone","you don't have that."}},1),
			action("use bone *stop wall","You wait until the walls draw nearer and wedge the bone between them. The very resiliant bone keeps them from moving further",{{"used_bone",true},{"has_bone",false}},-1,{{"has_bone",true}},{{"has_bone","You don't have that."}},1),
			action("stop wall with <any>","You don't have that."),
			action("stop wall","How will you stop it?"),
			action("break cuffs with wall","The spikes have drawn close enough for you to brush them with your restraints. They tear with relative ease",{{"broke_cuffs",true}},-1,{{"used_bone",true}},{{"used_bone","the spikes are much too far away to make contact with. And when they draw near enough you wouldn't have the time to escape with them still closing in."}},1),
			action("use wall *break cuffs","The spikes have drawn close enough for you to brush them with your restraints. They tear with relative ease",{{"broke_cuffs",true}},-1,{{"used_bone",true}},{{"used_bone","the spikes are much too far away to make contact with. And when they draw near enough you wouldn't have the time to escape with them still closing in."}},1),
			action("break cuffs with bone","The bone is not sharp enough to tear the cuffs.",{{}},-1,{{"has_bone",true}},{{"has_bone","You don't have that."}}),
			action("*go north","",{},1,{{"broke_cuffs",true}},{{"broke_cuffs","Your restraints keep you from moving"}}),
			action("go (look/talk) skeleton (break/sceptre around) wall","test"),
		}
	),
	scenario(
		//1
		"",
		{
			action("look around","You find yourself in a damp stone hallway faintly illuminated by narrow windows and that runs east to west. The door to your cell lies south. You hear footsteps coming from the west"),
			action("*go south","",{{}},0,{{}},{{}}),
			action("*go west","|You run into a group of armed guards. |When they see the sceptre that you are holding they immediately clear the way.",{{}},4,{{"has_sceptre",true},{"applied_suit",true}},{{"applied_suit","#You run into a group of armed guards who after finding you have not met with your demise quickly impale with their spears."},{"has_sceptre","|You run into a group of armed guards. They immediately ask where you are going and for what purpose. |Not knowing what to say, they pry the helmet from your head, revealing your identity|#They impale you with their spears and leave you to die."}}),
			action("*go east","",{{}},2,{{}},{{}}),
		}
	),
	scenario(
		//2
		"",
		{
			action("look around","You are at the end of a hallway of many beautiful tapestries, before a large oaken door, equipped with a knob and a stained-glass window. To either side of it are grand figures in suits of armour. Torches light the the vicinity, and a red rug lines the path towards it the door."),
			action("look window","You peer through the window and see two men in the same knight's uniform as in the statues outside, standing close to the other side of the door. The thickness of the glass prevents you from making out the details of anything further in the room."),
			action("look suit","The knight statues consist of a proper chestplate of iron as well as a helmet with a thick visor that practically obscures the face of the wearer."),
			action("look tapestry","The tapestries are woven with very vibrantly coloured fabrics. One such piece of art captivates your attention. It depicts a noble valiantly raising a golden sceptre to the sun, where it appears to shine light to the land beneath the noble's feet."),
			action("look torch","the torches are lit high above the opening of the door."),
			action("look rug","The rug is soft to the touch and has a deep red hue."),
			action("open door","The door is already open.",{{}},-1,{{"opened_door1",true}},{{"opened_door1","The door is locked"}}),
			action("knock door","You give the door a hearty thump with the brass knob. Immediately it swings open, and you are greeted by two knights. They nod to you and walk away. Perhaps they think you are here to take the next shift.",{{"opened_door1",true}},-1,{{"applied_suit",true}},{{"applied_suit","#You give the door a hearty thump with the brass knob. Immediately it swings open, and you are greeted by two knights. They look you up and done and immediately seize and drag you away. You do not know for sure you fate, but you fear execution will shortly follow.#"}},1),
			action("get suit","You yank one of the suits from its frame. Its pieces are remarkably lighter than you had anticipated.",{{"has_armour",true}},-1,{{"has_armour",false}},{{"has_armour","You see no need to get the other suit."}},1),
			action("wear suit","You sheepishly apply the chestplate sleeves, and other components to your person. At last you don the helmet, which limits your field of view quite profoundly. At any rate, the armour makes you feel less vulnerable.",{{"applied_suit",true}},-1,{{"has_armour",true}},{{"has_armour","You don't have that"}},1),
			action("*go east","",{{}},3,{{"opened_door1",true}},{{"opened_door1","The door is locked."}}),
			action("*go west","",{{}},1,{{}},{{}}),
		}
	),
	scenario(
		//3
		"",
		{
			action("look around","You appear to be in the treasury of the castle. You are surrounded by mounds of glimmering gold and crystal treasures. Standing erect amongst the mounds of wealth you see a glistening and bedazzled sceptre"),
			action("look (treasure/gold)","Gold coins scatter the room, forming a sea of large piles. Within them are assorted objects of the same lustre."),
			action("get (treasure/gold)","What treasure shall you take?"),
			action("get coins","There are too many to carry in your hands, and coins are only valuable in great quantities."),
			action("get coins with chamberpot","You tuck the chamberpot under your arm and greedily toss handfuls and handfuls of coins inside.",{{"has_coins",true}},-1,{{"has_coins",false},{"has_chamberpot",true}},{{"has_chamberpot","You don't have that."},{"has_coins","It's already full"}},1),
			action("get object","What object shall you take?"),
			action("look sceptre","The shining ruby at its head catches your eye. At first only a glimpse, you can no longer keep your eyes off it. It rests in a piles towards the corner of the room"),
			action("get sceptre","You wade your way through the sea of treasures and pluck the sceptre from its pile.",{{"has_sceptre",true}},-1,{{"has_sceptre",false}},{{"has_sceptre","You already have that"}},1),
			action("*go west","",{{}},2),
		}
	),
	scenario(
		//4
		"",
		{
			action("look around", "After wandering through the many halls you find yourself outside the castle. You are before many rolling hills, along which a dirt path leads. It run to the north."),
			action("look path","The path is made of dirt and gravel."),
			action("look hills","The eloquent hills are a mark of the beautiful landscape."),
			action("look castle","The castle is composed of large cobble-stone blocks, standing at least 30 meters high, with its turrets soaring to the skies. Taking note of the lack of windows, you are glad to finally be out of it."),
			action("*go south","You wish not to return to the castle whose lord imprisoned you."),
			action("*go north","|You made your way down the dirt road, still rought with fatigue and hunger from your harsh imprisonment| As you walk you take another gander at the sceptre you swindled from your incarcerator's castle. A closer inspection of it gives you a lapse of clarity as you remember why you ended up in the dungeon.| You are a travelling villein looking for work after being expelled from your fief. The baron of St. Aliquis had promised you work on his barony if you returned to him the sceptre he had lost to a feudal skirmish with the duke of Quelqueparte.| You hasten your pace as realize his hospility will soon be yours.",{{}},5)
		}
	),
	scenario(
		//5
		"",
		{	
			action("look around","You find yourself in the  center of the bustling keep of the castle. You see many common men go about their work with much clamour and hubbub. To the north is the great donjon, to the west a group of residential buildings, to the east the graveyard, and to the south the entrance of the castle."),
			action("*go north","",{{}},6),
			action("*go south","",{{}},8),
			action("*go east","",{{}},14),
			action("*go west","",{{}},17),
		}
	),
	scenario(
		//6
		"",
		{
			action("look around","You are before the great tower of the castle. It stands majestically above the enclosing walls of the keep. A large doors lies in front northwards, and around it are many decorative gardens of flowers and other vegetation, to which a gardener is tending. The way back is south."),
			action("look bushes","The hedges surrounding the donjon are dense both in volume and in vibrant flowers. Patterns of blue, yellow and pink dot the surface of the lush green bushes."),
			action("check bushes","You reach your hand inside the bushes, and to your wonder discover... A shovel! Seeing no one around to be using it otherwise, you decide to borrow it for the time being",{{"has_shovel",true}},-1,{{"has_shovel",false}},{{"has_shovel","You reach into the bush... and find nothing."}},1),
			action("talk gardener","'I saw her rise from her grave!', he wails. 'The witch walks the earth!' You take a few steps back."),
			action("talk gardener witch","He continue to ramble incoherently"),
			action("give seeds gardener","You present the man with the seeds, and he seems to calm down a little. A toothy smile appears on his face as he checks the contents, 'ah, thank-ya. Take 'his for yer troubles.' He give you a handful of francs'",{{"has_francs",true},{"has_seeds",false}},-1,{{"has_seeds",true}},{{"has_seeds","You don't have that"}},1),
			action("*go north","",{{}},7),
			action("*go south","",{{}},5)
		}
	),
	scenario(
		//7
		"",
		{
			action("look around","After climbing the many stairs, you find yourself in the great chamber of the baron. He sits on a throne of gold and velvet, atop a short staircase. Surrounding and illuminating the round room are many stained glass windows that stretch from the floor to the ceiling."),
			action("look *glass window","The windows depict various biblical scenes: The deception of man, the great flood, the resurrection of christ, to name a few."),
			action("look throne","The throne is made of gold and lined with purple velvet. This lord is very wealthy for the mere status of baron."),
			action("look baron","The baron sits quite non-chalantly upon the throne. He dons a modest crown of silver and three small jewels."),
			action("talk baron","|The baron sees you and in humour inquires,'Have you already recovered the sceptre of Saint. Peter?' His coyness turns to astonishment as you reveal it from your robe and present it to him|'By god, you have demonstrated diligence and compentence of enormous  proportion'. He pauses, appearing comtemplative in thought. At lasts he speaks.|'I have one final task for you, if you seek a greater reward. When I ushered you away from my estate with the impossible task of recovering my heirloom, I anticipated you'd never return. Yet you have succeeded all expectations I should have for a lowly villein.|I sense you may in fact be a man of noble blood. To prove this is so, I present to you a test feasible by a man only of the most gentle kind: Defeat the witch which has laid siege to our harvests and the wellbeing of my citizens.|If you succeed, I shall elevate your status from that of a commoner to a knight under my loyalty. Shall you accept?|You enthusiastically nod your head. He continues: 'I know little of her dwellings or her motives, but she is a practitioner of witchcraft nonetheless. You are to complete the task with your ingenuity and resourcefulness. I shall leave you with only my brooch as proof of your service to me. Now go!'",{{"got_quest",true},{"has_brooch",true},{"has_sceptre",false}},-1,{{"got_quest",false}},{{"got_quest","You ought not to return to the baron until your quest is finished."}},1),
			action("*go south","",{{}},6)
		}
	),
	scenario(
		//8
		"",
		{
			action("look around","You find yourself at the outset of a chiming forest. An opening into the dense woods faces south. Remnants of an abandoned encampment are strewn about on the ground There is a cave distantly east. The field continues to the west"),
			action("look ground",""),
			action("*go (cave/east)","",{{}},9),
			action("*go north","",{{}},5),
			action("*go west","",{{}},11),
			action("*go south","|The begin your trek into the cave, map in hand",{{}},12,{{"has_map",true}},{{"has_map","|You enter the abode of the forest.|After wandering for some time, you find yourself back at the entrance to the forest where you began"}}),
			action("look camp","There are remnants of a fire, including a of charred pieces of wood stacked together, surrounded by a circle of stones. On a nearby tree a rope swings in the breeze, fastened to a high branch."),
			action("climb tree","It appears as though this tree is too thick and branch-deficient to climb"),
			action("get stones","You grab a few of the stones surrounding the fire pit",{{"has_stones",true}},-1,{{"has_stones",false}},{{"has_stones","You see no need to get more stones"}},1),
			action("get rope","You already have that",{},-1,{{"has_rope",true}},{{"has_rope","You rope is fastened to the tree above"}}),
			action("cut rope","With what will you cut the rope?",{{}},-1,{{"has_rope",false}},{{"has_rope","You see no need to do that"}}),
			action("cut rope with sword","You position yourself, draw the sword, and heave it in the direction of the rope. The rope tears with minimal resistance",{{"has_rope",true}},-1,{{"has_rope",false},{"has_sword",true}},{{"has_rope","You already have that"},{"has_sword","You don't have that"}},1),
			action("start fire","How will you do that?"),
			action("start fire *with flint and steel","You kneel down and begin to kindle the fire. Within minutes you have a steady flame burning",{{"started_fire",true}},-1,{{"started_fire",false},{"has_flint_and_steel",true}},{{"started_fire","You already did that"},{"has_flint_and_steel","You don't have that"}},1),
			action("(use/light) lantern with fire","You share the flame from the fire with your lantern",{{"lit_lantern",true}},-1,{{"lit_lantern",false},{"has_lantern",true}},{{"lit_lantern","You already did that"},{"has_lantern","You don't have that"}},1)
		}
	),
	scenario(
		//9
		"",
		{
			action("look around","The interior of the cave is pitch black. Through the echo of your motions you discern it is of great size. The way out is west",{{}},-1,{{"lit_lantern",false}},{{"lit_lantern","The expanse of the cave reveals itself. There are deep chasms to your left and right, deep enough that the light can not penetrate its end. In front of you bearing east is a jagged path to the back, where a large stone door stands below a crude chiseled skull. The way out is west"}}),
			action("unlock door with *skull key","The key scrapes across the teeth of the lock, you heave it with oth hands to turn the lock. Suddenly, a deep click bellows across the interior, the with the grating of stone you see the mighty door reveal the way.",{{"opened_door4",true}},-1,{{"has_skull_key",true},{"lit_lantern",true},{"opened_door4",false}},{{"opened_door4","The door has already been unlocked"},{"has_skull_key","You don't have that"},{"lit_lantern","That doesn't seem possible"}},1),
			action("*go west","",{{}},8),
			action("*go east","",{{}},10,{{"opened_door4",true}},{{"opened_door4","The door is locked"}}),
		}
	),
	scenario(
		//10
		"",
		{
			action("look around","You are in the witch Hagatha's lair. The room is dimly lit and lined with cobblestone. Plundered treasure and stolen harvest crops are strewn about. A chandelier hangs overhead. The witch stands decrepitly before you"),
			action("look witch","She wears a dark, grey tattered robe and a pointed cap. Her skin emanates a sickly grey hue, as if life itself with drained from it. In spite of this, she stands with a hunched posture, and beams at you with red eyes"),
			action("talk witch","You rebuke the witch, but she pays no heed to God's will.",{{}},-1,{{"used_sword",false},{"cut_chandelier",false},{"has_wand",false}},{{"used_sword","She tests your faith: 'You and all the peoples of this land' are slaves to Jehoavah, only the through the prince of darkness can you pursue your own destiny'"},{"cut_chandelier","My soul will not leave this world until Lucifer's redemtpion, you are powerless against me!'"},{"has_wand","She wails, 'Your god is false!'"}}),
			action("kill witch with sword","You lunge at her with your sword and strike her through the heart. She falls over backwards, but cackles loudly, 'You can not defeat me with earthly weapons alone. My power is drawn from beyond this world!' She quickly rises upright, seemingly by forces unknown.'",{{"used_sword",true}},-1,{{"used_sword",false}},{{"used_sword","It's no use"}},1),
			action("cut (chandelier/rope)","The chandelier is to far out of reach.",{{}},-1,{{"cut_chandelier",false}},{{"cut_chandelier","You already knocked it down"}}),
			action("throw sword (chandelier/rope)","|In a last ditch effort, you heave the sword at the chendlier in a spinning motion. No longer underestimating your abilities, the rope tears as intended|The chandelier falls with a cacophonous crash onto the witch. She drops her wand during the impact, but continues to laugh maniacly",{{"cut_chandelier",true}},-1,{{"cut_chandelier",false}},{{"cut_chandelier","You already knocked it down"}},1),
			action("get wand","You scramble to grab the wand before Hagatha regains her footing",{{"has_wand",true}},-1,{{"cut_chandelier",true},{"has_wand",false}},{{"cut_chandelier","You already knocked it down"},{"has_wand","You already have that"}},1),
			action("use wand witch","|You point the wand at the witch and will her away in the name of the lord.|Nothing comes to motion|She laughs,'Foolish you are, for only I and those who know my name can use my occultish power, and for 500 years it has been bestowed on only dead ears'|With this revelation you correct your rebuke: 'By God's providence, I cast out the heretic, Genevieve of Hagatha to the bowels of hell where her sins beckon her!'|With these words, she reaches to her heart in recoil, and falls dead.| Exhausted, you hurry back to the castle.| In the throneroom, you cast the witch's head at the barons feet. He scans her remains, and with a solemn nod ushers his attendants to retrieve his sword. He rises and knights you to nobility, as a vassal of St. Aliquis",{{"killed_witch",true}},22,{{"has_wand",true},{"read_name",true}},{{"read_name","|You point the wand at the witch and will her away in the name of the lord.|Nothing comes to motion|She laughs,'Foolish you are, for only I and those who know my name can use my occultish power, and for 500 years it has been bestowed on only dead ears'|#A flash of light stabs your eyes, and you are overcome with horrid convulsions. You fall dead shortly after"},{"has_wand","You don't have that"}},2),
			action("*go west","#You turn your back on the witch and towards the door. Suddenly you jolt with horrible convulsions. You fall forwards, and the world loses colour. In your last moments you hear a gurgle: 'Never overlook Satan's wrath")
		}
	),
	scenario(
		//11
		"",
		{
			action("look around","You are in an open field, cluttered with pieces of foliage. There is a bush, a stump, and river which runs from north to south. On top of the river stands a martello tower, with gates the passage of the stream running through its ground floor. On the lookout stands a man wearing a chainmail vest and a visor.",{{}},-1,{{"threw_stones",false}},{{"threw_stones","You are in an open field, cluttered with pieces of foliage. There is a bush, a stump, and river which runs from north to south. On top of the river stands a martello tower, with gates the passage of the stream running through its ground floor. A man's corpse lays splayed against the soft ground."}}),
			action("(look/check) stump","You find nothing interesting"),
			action("(look/check) bushes","You find nothing interesting"),
			action("look man","The man wears a knight's visor and light chainmail armour"),
			action("*go east","",{{}},8),
			action("*go west","The river blocks your path"),
			action("talk man","He's dead",{{}},-1,{{"threw_stones",true}},{{"threw_stones","You shout in his direction, but you can't seem to get his attention"}}),
			action("throw stones","Where will you throw them?",{{}},-1,{{"has_stones",true}},{{"has_stones","You don't have that"}}),
			action("throw stones man","You toss a stone in his general direction. You underestmate your aim. The rock hits him straight in the forehead, and he stumbles to the edge of the balcony as he lets out a cry, and ... holy crap! You killed him! He falls to his death on the ground below you. Perhaps you should have chosen a smaller rock",{{"threw_stones",true}},-1,{{"has_stones",true},{"threw_stones",false}},{{"threw_stones","You decide not to further desecrate his corpse"},{"has_stones","You don't have that"}},1),
			action("check (man/body)","You rummage through his pockets and find... a gold key!",{{"has_gold_key",true}},-1,{{"threw_stones",true},{"has_gold_key",false}},{{"has_gold_key","There's nothing else there"},{"threw_stones","You can't do that"}},1)
		}
	),
	scenario(
		//12
		"",
		{
			action("look around","You find yourself in a small clearing in the woods whera a small log cabin resides. A man wearing a helmet and grasping a sword sits on the porch, fidgeting with nervous mannerisms.",{{}},-1,{{"killed_man",false}},{{"killed_man","You find yourself in a small claring in the woods where a small log cabin resides. A man lays sprawled out in the porch, tainted with blood"}}),
			action("talk man","As you call to him his head snaps in your direction. With a shaky voice, he explains: 'We were decimated out there. Let the witch's powers not be underestimated. Out of fifteen men, I was the only to survive her onslaught of satanic magic. I will not dare to face her again, or the baron. But with no army left to fight, her reign will surely never end.'"),
			action("*go north","",{{}},8),
			action("*go south","",{{}},13,{{"opened_door3",true}},{{"opened_door3","The door to the cabin is locked"}}),
			action("get sword","You ask for the sword, but clutching it to his chest he says: 'What could you need with this? If not I, the king's vassal could not vanquish her, what makes you think you could?'",{{}},-1,{{"has_sword",false}},{{"has_sword","You already have that"}}),
			action("(give/show) brooch *man","You reach into your robes and present him with the shining brooch. His eyes widen and glimmer with its reflection. 'The baron sent you?' He asks, with a hint of exasperation. His mind races. At last, he thrusts the sword into your arms, 'Take this, and don't tell the baron that I'm alive",{{"has_sword",true}},-1,{{"has_sword",false}},{{"has_sword","You see no need to show him the brooch again"}},1),
			action("kill man with sword","You draw the sword and strike the man in the chest. He keels over onto the floor, sputtering, 'God curse your soul', and dies.",{{"killed_man",true}},-1,{{"killed_man",false},{"has_sword",true}},{{"killed_man","He's already dead"},{"has_sword","You don't have that"}},1),
			action("check (man/body)","You check his pockets and find ... a silver key!",{{"has_silver_key",true}},-1,{{"has_silver_key",false},{"killed_man",true}},{{"has_silver_key","You check his pockets and find... nothing"},{"killed_man","Nothing stands out about him"}},1),
			action("(unlock/use) (door/cabin) with key","The key fits, and the door clicks open.",{{"opened_door3",true}},-1,{{"opened_door3",false},{"has_silver_key",true}},{{"opened_door3","It's already unlocked"},{"has_silver_key","You don't have that"}},1)
		}
	),
	scenario(
		//13
		"",
		{
			action("look around","You find yourself inside the tiny cabin. A bed fills the left side of the room, and on the right is a primitive wooden table on which lies a sparkling jewel and many cutting tools."),
			action("*go north","",{{}},12),
			action("get jewel","You snatch the jewel from its holder",{{"has_jewel",true}},-1,{{"has_jewel",false}},{{"has_jewel","You already have that"}}),
			action("look walls","The bed is well-worn and stained with dirt and grime."),
			action("look table","The table is made from freshly cut logs. On top of it lays a few metal tools and a glistening jewel."),
			action("look tools","The tools look to be for various stone-cutting tasks, although you are not educated enough to identify them"),
			action("look jewel","The jewel has a deep red hue, and glistens in sunlight. To stare into it is mesmerizing, as if a portal to a sed of red"),
		}
	),
	scenario(
		//14
		"",
		{
			action("look around","You find yourself in a desolate grave yard. In the centre of the field is the abbey, to the north, on top of which crouches a menacing gargoyle. To the left is a tombstone which appears to have been dug up. A crooked tree stands tall next to it, and the wind howls through its branches. To the right are a number of other gravestones. A gravekeeper skulks around tiredly.",{},-1,{{"gave_shovel",false},{"in_tree",false}},{{"in_tree","You see the field dotted with small gravestones. On the roof of the abbey, you see the gargoyle in all its fearsomenes. Below it are words written along the buttresses of the building"},{"gave_shovel","You find yourself in a desolate grave yard. In the centre of the field is the abbey, to the north, on top of which crouches a menacing gargoyle. To the left is a tombstone which appears to have been dug up. A crooked tree stands tall next to it, and the wind howls through its branches. To the right are a number of other gravestones."}}),
			action("look (abbey/words)","The abbey is made with modest materials, but with passionate craftsmanship. The arched door has large brass hinges, and the stone rim is marked with many spiralling and tapering designs. the roof features impressive buttresses made of finely chiseled stone",{},-1,{{"in_tree",false}},{{"in_tree","You see words engraved deeply on the roof top 'LET THE HEAVENS WEEP TO THE CALL OF JEHOVAH"}}),
			action("say jehovah","|With a pensive expression, you loudly utter the lord's name. As your lips close, the scene falls silent.|Suddenly, a flash of lightning shakes the earth. In an instant, the skies are imbued with clouds and the thick sheet of rainfall. Running, you seek shelter under the tree.| After several minutes, the storm abruptly stops. Sunlight bursts into the scene once again.",{{"said_words",true},{"in_tree",false}},-1,{{"said_words",false}},{{"said_words","You prefer not to invoke the wrath of the lord a second time"}},1),
			action("look tombstone","The tombstone is tall and decored with wonderful arches and architectural details. Atop the grave you read the following: 'Here lies the wretch, GENEVIEVE of HAGATHA, ?-1220. May she rot in the deepest circle of hell alongside Judas' Immediately below it appears as though the ground was unearthed with great fervour.",{{"read_name",true}},-1,{{"said_words",true}},{{"said_words","The tombstone is tall and decored with wonderful arches and architectural details. Atop where the name and date would logically reside there is a thick layer of dirt. Immediately below it appears as though the ground was unearthed with great fervour."}},1),
			action("look tree","The tree resembles a witherig old man with an unsteady gait. A nook in its centre peers at you. Swinging in the cool breeze is a creaking lantern with an unlit candle."),
			action("look grave","These graves are more modest. Attest to the lives of many men who primarily lived in the last century. Among their names are: GALEN GARNIER ALIENOR FRANCOIS, PHILIP BOURBON II"),
			action("look gravekeeper","The poor wretch looks better fit to reside under the ground than upon it. He walks in an obscene hunch, and his arms hang pitifully with despair. You try not to glance at him often, but at least once already your gazes have met."),
			action("look hole","The approach the hole and peer into it. The extent of it is much deeper than you had thought. Down into the earth your observe claw marks along the cobble-stone walls"),
			action("*go west","",{},5),
			action("(go abbey/go north)","",{{}},16,{{"gave_shovel",true}},{{"gave_shovel","It's locked"}}),
			action("dig *up grave","|With a quick sweeping glance from left to right, you pitch the shovel and begin heaving mound upon mound of dirt from its abode, beaming with greed| After some time you here the clunking of wood against your shovel. You unearth frail a coffin, and break its latches open with relative ease. Inside you find the decomposed body of a monarch past.| He wears a fine robe, and an immensely bejewelled crown. You pry it from his skull, and leap from the earth",{{"has_crown",true}},-1,{{"has_shovel",true},{"gave_shovel",true}},{{"gave_shovel","You draw the shovel but here yelling across the field. 'Ey! Let the dead be dead!', it screams.'"},{"has_shovel","With what will you dig with?"}},1),
			action("talk gravekeeper","You approach the gravekeep and inquire about the witch Hagatha. He doesn't indulge you, instead he complains about having to search for his lost shovel, whilst he should be sleeping for his night shift",{},-1,{{"gave_shovel",false}},{{"gave_shovel","He isn't here"}}),
			action("give shovel gravekeeper","He makes little more conversation, but musters up a crooked smile and grumbles with glee as he takes the shovel. He waddles back to the abbey, and you think you hear a sentiment of thanks amidst  his mumurs",{{"gave_shovel",true},{"has_shovel",false}},-1,{{"gave_shovel",false},{"has_shovel",true}},{{"has_shovel","You don't have that"},{"gave_shovel","He isn't here"}},1),
			action("tie rope tree","You wrap the rope around the thick trunk of the tree",{{"tied_rope",true},{"has_rope",false}},-1,{{"tied_rope",false},{"has_rope",true}},{{"has_rope","You don't have that"},{"tied_rope","You've already done this"}},1),
			action("go hole","You begin your descent down the hole",{},15,{{"tied_rope",true}},{{"tied_rope","You peer into the hole and find it much deeper than you had initially assumed. In fact it is far too deep to descend safely"}}),
			action("climb tree","You ascend the oaken tower.",{{"in_tree",true}},-1,{{"in_tree",false},{"gave_shovel",true}},{{"gave_shovel","As you mount yourself to climb you hear yelling across the field. 'Get outta 'there', the gravekeeper cries"},{"in_tree","You are already in the tree"}},1),
			action("*go *climb descend *tree","You carefully make your way down the tree",{{"in_tree",false}},-1,{{"in_tree",true}},{{"in_tree","You are not in the tree"}}),
			action("get lantern","While clinging to a sturdy branch and with an outstretched arm, you grasp for, and at last grab the lantern",{{"has_lantern",true}},-1,{{"in_tree",true},{"has_lantern",false}},{{"has_lantern","You already have that"},{"in_tree","The lantern is far too high in the tree for you to reach it"}},1)
		}
	),
	scenario(
		//15
		"",
		{
			action("look around","You find yourself in a cramped tomb. The floor, walls, and ceiling are lined with cobblestone. An open coffin lies ahead. Marking are on the wall behind. The hole from which you come lies west"),
			action("look coffin","The coffin is wooden, with large brass hinges. Strangely enough, there is a lock on top of the lid. Scratch marks line the surface."),
			action("look wall","The writing are in latin, but you understand the general message."),
			action("*go west","",{},14),
			action("check coffin","You look inside the coffin and find... a key headed with a small skull.",{{"has_skull_key",true}},-1,{{"has_skull_key",false}},{{"has_skull_key","You look inside the coffin and find... nothing"}},1)
		}
	),
	scenario(
		//16
		"",
		{
			action("look around","The abbey has bleak stone walls. On the left is a bed, where the gravekeeper sleeps. To the right is a desk"),
			action("look desk","The desk is large and has many drawers built into it. On top of it is a crumpled note with many tear marks"),
			action("read note","The note reads: 'October 12: There are many ill forces at work on these grounds. Today the heretic Hagatha's grave was unearthed in a most unnatural fashion. I saw only a struck of lightning, and not long after, she emerged from hell."),
			action("get note","You don't need it"),
			action("check (drawer/desk)","You check the drawers and find the second half of the note. It reads: 'October 3, On the request of good baron of St. Aliquis, the late king Phillip II has been buried in this small yard, on account of the civil unrest his reign bred that may stir temptations to desecrate his body, or steal the many regal ornaments his attire dons upon him'"),
			action("(look/check) bed","The bed and its sheets are modest at best. The mattress is suspended high above the ground by its supports"),
			action("(look/check) under bed","You check under the bed and find the shovel you gave him. You decide to borrow it once again",{{"has_shovel",true}},-1,{{"has_shovel",false}},{{"has_shovel","There's nothing else there"}},1),
			action("*go south","",{{}},14)
		}
	),
	scenario(
		//17
		"",
		{
			action("look around","You see three slender houses fit tightly down the lane northwards. The one on the left has a mailbox and a fine finish. The one on the left is tattered, and the door is heavily splintered. The middle is in modest condition. On the other side of the street you a market stall with a sign on it. Down towards the end of the street east is the base of a large clocktower.",{{}},-1,{{"fixed_clock",false}},{{"fixed_clock","You see three slender houses fit tightly down the lane. The one on the left has a mailbox and a fine finish. The one on the left is tattered, and the door is heavily splintered. The middle is in modest condition. On the other side of the street you a man tending to a market stall. Down towards the end of the street east is the base of a large clocktower."}}),
			action("look houses","The residencies have a humble appearance. Thatched-roofs shelter the single story, and the windows panes are imbued with dust and grime."),
			action("go middle house",""),
			action("look sign","The sign is gone",{{}},-1,{{"fixed_clock",true}},{{"fixed_clock","The sign says: 'Store opens at noon'"}}),
			action("look tower","The tower stands some thirty meters high. is made of a smootly-finished cobblestone. The face of the clock is a marvel of calligraphic art, with arching and spiralling beams signifying and decorating the hours and the hands."),
			action("look man","The man wears lavishly clothing, a mark of a wealthy and competent merchant. In spite of this, he appears glum, as if fallen on hard times.",{{}},-1,{{"fixed_clock",true}},{{"fixed_clock","Look at what?"}}),
			action("(look clock/check time)","The hands of the clock wind slowly and with the frailty of an old man. By now, it reads well past twelve.",{{}},-1,{{"fixed_clock",true}},{{"fixed_clock","The time is 11:45 AM. There is no hand to count seconds, but when staring at it you find that the time passes very slowly, if at all."}}),
			action("*go (west/clocktower)","",{{}},18,{{"opened_door2",true}},{{"opened_door2","The door to the clocktower is locked"}}),
			action("*go east","",{{}},5),
			action("*go north","",{{}},19),
			action("(unlock/use) (door/clocktower) with *gold key","The key fits, and the door clicks open.",{{"opened_door2",true}},-1,{{"opened_door2",false}},{{"opened_door2","It's already unlocked"},{"has_gold_key","You don't have that"}},1),
			action("talk (man/shopkeeper)","You inquire the man about his business. 'I'll give you something good if you've got the money', he says with a sly smile",{{}},-1,{{"has_map",false}},{{"has_map","'Sorry, my inventories clean empty', he says"}}),
			action("give francs (man/shopkeeper)","'This'll do it', he says, 'Here you are'. He hands you an old and tattered map",{{"has_francs",false},{"has_map",true}},-1,{{"has_francs",true}},{{"has_francs","You don't have that"}},1),
			action("give <any> (man/shopkeeper)","'Sorry, I only take francs'",{{}},-1,{{"has_map",false}},{{"has_map","'Sorry, I'm fresh out of goods'."}})
		}
	),
	scenario(
		//18
		"",
		{
			action("look around","After climbing a helix of stairs, you find yourself immersed in the mechanism of the clocktower. The symphonic clicking and grinding of gears and cogs fills your eardrums. The interior is dark, save for a band of light emanating from the face of the clock. In a nest of gears directly behind the face, you spot a mallet encroached inside the machine.",{{}},-1,{{"has_mallet",false},{"fixed_clocks",false}},{{"has_mallet","After climbing a helix of stairs, you find yourself immersed in the mechanism of the clocktower. The symphonic clicking and grinding of gears and cogs fills your eardrums. The interior is dark, save for a band of light emanating from the face of the clock. A mallet lies on the platform before you"},{"fixed_clock","After climbing a helix of stairs, you find yourself immersed in the mechanism of the clocktower. The symphonic clicking and grinding of gears and cogs fills your eardrums."}}),
			action("look gears","The gears fit the description as such only loosely. Their shape is assymmetric, many with teeth to thin or too fat. Unsurprisingly, they cry with great fervour as they turn."),
			action("*go east","",{{}},17),
			action("get mallet","You pick up the mallet",{{"has_mallet",true}},-1,{{"fixed_clock",true},{"has_mallet",false}},{{"has_mallet","You already have that"},{"fixed_clock","The mallet is too far out of reach to grasp for"}},1),
			action("throw stones mallet","You heave a hefty rock at the mallet. By virtue of your throwing ability you are able to dislodge the mallet. It falls to the ground, creating a cascade of noise as it knocks against one gear to another.",{{"fixed_clock",true}},-1,{{"fixed_clock",false}},{{"fixed_clock","You already have that"}},1)
		}
	),
	scenario(
		//19
		"",
		{
			action("look around","You find yourself inside the run-down house. A splintered wooden table stands in the center, surrounded by equally worn-down stools. Towards the back, next to the fireplace, you see a dusty chest, held shut with a thick lock.",{{}},-1,{{"broke_lock",false}},{{"broke_lock","You find yourself inside the run-down house. A splintered wooden table stands in the center, surrounded by equally worn-down stools. Towards the back, next to the fireplace, you see a dusty chest with the lock busted open."}}),
			action("*go south","",{{}},17),
			action("look fire","The fireplace seems long past its days of kindling fire. The ashes of wooden logs is submerged by stone rubble and debris of various kinds."),
			action("look chest","The chest is of modest craftsmanship, with wooden sides and brass edges."),
			action("look lock","The lock is crudely thick, having an almost cubical shape."),
			action("break (lock/chest) with mallet","With all your strength, you bludgeon the padlock. After a few swings, it finally gives way.",{{"broke_lock",true}},-1,{{"broke_lock",false}},{{"broke_lock","You've already done that"}},1),
			action("check chest","You open the lid, and find inside... A bag of seeds. It must be a valuable breed",{{"has_seeds",true}},-1,{{"has_seeds",false},{"broke_lock",true}},{{"has_seeds","You find nothing else in the chest"},{"broke_lock","The chest is locked"}},1),
			action("check fire","You check inside the fireplace and find: A set of flint and steel!",{{"has_flint_and_steel",true}},-1,{{"has_flint_and_steel",false}},{{"has_flint_and_steel","You find nothing else of interest in the fire place"}},1)
		}
	),
	scenario(
		//20
		"",
		{
			action("look around","You find yourself inside the next house over."),
		}
	),
	scenario(
		//21
		"",
		{
			action("<any>","You are dead. Type 'restart' to start a new game, or load 1,2,3 to restore a saved game")
		}
	),
	scenario(
		//22
		"",
		{
			action("<any>","Thanks for playing Dungeon Quest. Type 'restart' to start a new game, or load 1,2,3 to restore a saved game")
		}
	)
};

int scenario_num = 0;

int score = 0;

