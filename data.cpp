#include <string>
#include <vector>
#include <map>

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
	{"door","bars"},
	{"cuffs","shackles","chains"},
	{"use"},
	{"with","using","by"},
	{"stop","wedge"},
	{"break","tear","rip","slice","shear"},
	{"start","begin"},
	{"suit","suits","armour","statue","statues"},
	{"window"},
	{"glass"},
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
	{"castle","tower","fortress","clocktower"},
	{"bushes","bush","hedge","hedges"},
	{"throne","seat"},
	{"baron","king","lord"},
	{"gardener"},
	{"flip","turn","pull","flick"},
	{"lever","switch"},
	{"lantern","candle","light"},
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
	{"drawer"},
	{"note","notes","diary","sign"},
	{"bed","mattress"},
	{"under","beneath"},
	{"man","guard","knight"},
	{"stones","stone","rocks","rock","pebbles"},
	{"throw","chuck"},
	{"clock","face"},
	{"key"},
	{"unlock"},
	{"read"}
};

map<string,bool> conditions = {
	{},
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
	{"has_lantern",false},
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
	{"has_key",false},
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
	{"key","The key is a glimmering gold colour"}
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
			action("get bone *skeleton","you pry a bone from the rib-cage of the skeleton",{{"has_bone",true}},-1,{{"has_bone",false}},{{"has_bone","You see no need to get another bone"}}),
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
			action("*go west","|You run into a group of armed guards. |When they see the sceptre that you are holding they immediately clear the way.",{{}},4,{{"applied_suit",true},{"has_sceptre",true}},{{"applied_suit","#You run into a group of armed guards who after finding you have not met with your demise quickly impale with their spears."},{"has_sceptre","|You run into a group of armed guards. They immediately ask where you are going and for what purpose. |Not knowing what to say, they pry the helmet from your head, revealing your identity|#They impale you with their spears and leave you to die."}}),
			action("*go east","",{{}},2,{{}},{{}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You are at the end of a hallway of many beautiful tapestries, before a large oaken door, equipped with a knob and a stained-glass window. To either side of it are grand figures in suits of armour. Torches light the the vicinity, and a red rug lines the path towards it the door."),
			action("look window","You peer through the window and see two men in the same knight's uniform as in the statues outside, standing close to the other side of the door. The thickness of the glass prevents you from making out the details of anything further in the room."),
			action("look suit","The knight statues consist of a proper chestplate of iron as well as a helmet with a thick visor that practically obscures the face of the wearer."),
			action("look tapestry","The tapestries are woven with very vibrantly coloured fabrics. One such piece of art captivates your attention. It depicts a noble valiantly raising a golden sceptre to the sun, where it appears to shine light to the land beneath the noble's feet."),
			action("look torch","the torches are lit high above the opening of the door."),
			action("look rug","The rug is soft to the touch and has a deep red hue."),
			action("open door","The door is already open.",{{}},-1,{{"door1_open",true}},{{"door1_open","The door is locked"}}),
			action("knock door","You give the door a hearty thump with the brass knob. Immediately it swings open, and you are greeted by two knights. They nod to you and walk away. Perhaps they think you are here to take the next shift.",{{"door1_open",true}},-1,{{"applied_suit",true}},{{"applied_suit","#You give the door a hearty thump with the brass knob. Immediately it swings open, and you are greeted by two knights. They look you up and done and immediately seize and drag you away. You do not know for sure you fate, but you fear execution will shortly follow.#"}}),
			action("get suit","You yank one of the suits from its frame. Its pieces are remarkably lighter than you had anticipated.",{{"has_armour",true}},-1,{{"has_armour",false}},{{"has_armour","You see no need to get the other suit."}}),
			action("wear suit","You sheepishly apply the chestplate sleeves, and other components to your person. At last you don the helmet, which limits your field of view quite profoundly. At any rate, the armour makes you feel less vulnerable.",{{"applied_suit",true}},-1,{{"has_armour",true}},{{"has_armour","You don't have that"}}),
			action("*go east","",{{}},3,{{"door1_open",true}},{{"door1_open","The door is locked."}}),
			action("*go west","",{{}},1,{{}},{{}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You appear to be in the treasury of the castle. You are surrounded by mounds of glimmering gold and crystal treasures. Standing erect amongst the mounds of wealth you see a glistening and bedazzled sceptre"),
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
			action("*go north","|You made your way down the dirt road, still rought with fatigue and hunger from your harsh imprisonment| As you walk you take another gander at the sceptre you swindled from your incarcerator's castle. A closer inspection of it gives you a lapse of clarity as you remember why you ended up in the dungeon.| You are a travelling villein looking for work after being expelled from your fief. The baron of St. Aliquis had promised you work on his barony if you returned to him the sceptre he had lost to a feudal skirmish with the duke of Quelqueparte.| You hasten your pace as realize his hospility will soon be yours.",{{}},5)
		}
	),
	scenario(
		"",
		{	
			action("look around","You find yourself in the  center of the bustling keep of the castle. You see many common men go about their work with much clamour and hubbub. To the north is the great donjon, to the west a group of residential buildings, to the east the graveyard, and to the south the entrance of the castle."),
			action("*go north","",{{}},6),
			action("*go south","",{{}},8),
			action("*go east","",{{}},10),
			action("*go west","",{{}},11),
		}
	),
	scenario(
		"",
		{
			action("look around","You are before the great tower of the castle. It stands majestically above the enclosing walls of the keep. A large doors lies in front northwards, and around it are many decorative gardens of flowers and other vegetation, to which a gardener is tending. The way back is south."),
			action("look bushes","The hedges surrounding the donjon are dense both in volume and in vibrant flowers. Patterns of blue, yellow and pink dot the surface of the lush green bushes."),
			action("check bushes","You reach your hand inside the bushes, and to your wonder discover... A shovel! Seeing no one around to be using it otherwise, you decide to borrow it for the time being",{{"has_shovel",true}},-1,{{"has_shovel",false}},{{"has_shovel","You reach into the bush... and find nothing."}}),
			action("talk gardener","'I saw her rise from her grave!', he wails. 'The witch walks the earth!' You take a few steps back."),
			action("talk gardener witch","He continue to ramble incoherently"),
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
			action("look around","You find yourself at the outset of a chiming forest. An opening into the dense woods faces south. Remnants of an abandoned encampment are strewn about on the ground There is a cave distantly east. The field continues to the west"),
			action("look ground",""),
			action("*go (cave/east)","",{{}},99),
			action("*go west","",{{}},99),
			action("*go south","|The begin your trek into the cave, map in hand",{{}},99,{{"has_map",true}},{{"has_map","|You enter the abode of the forest.|After wandering for some time, you find yourself back at the entrance to the forest where you began"}}),
			action("look camp","There are remnants of a fire, including a of charred pieces of wood stacked together, surrounded by a circle of stones. On a nearby tree a rope swings in the breeze, fastened to a high branch."),
			action("get stones","You grab a few of the stones surrounding the fire pit",{{"has_stones",true}},-1,{{"has_stones",false}},{{"has_stones","You see no need to get more stones"}})
			action("get rope","You already have that",{},-1,{{"has_rope",true}},{{"has_rope","You rope is fastened to the tree above"}}),
			action("cut rope sword","You already have that",{{"has_rope",true}},-1,{{"has_rope",false},{"has_sword",true}},{{"has_rope","You already have that"},{"has_sword","You don't have that"}}),
		}
	),
	scenario(
		"",
		{
			action("look around","The interior of the cave is pitch black. Through the echo of your motions you discern it is of great size.",{{}},-1,{{"used_lantern",false}},{{"used_lantern",""}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You are in the wtich Hagatha's lair."),
		}
	),
	scenario(
		"",
		{
			action("look around","You are in an open field, cluttered with pieces of foliage. There is a bush, a stump, and river which runs from north to south. On top of the river stands a martello tower, with gates the passage of the stream running through its ground floor. On the lookout stands a wearing a chainmail vest and a visor."),
			action("*go east","",{{}},99),
			action("*go west","The river blocks your path"),
			action("talk man","He's dead",{{}},-1,{{"threw_rock",true}},{{"threw_rock","You shout in his direction, but you can't seem to get his attention"}}),
			action("throw stones","Where will you throw them?",{{}},-1,{{"has_stones",true}},{{"has_stones","You don't have that"}}),
			action("throw stones man","You toss a stone in his general direction. You underestmate your aim. The rock hits him straight in the fall, and he stumbles to the edge of the balcony as he lets out a cry, and ... holy crap! You killed him! He falls to his death on the ground below you. Perhaps you should have chosen a smaller rock",{{"threw_rock",true}},-1,{{"has_stones",true},{"threw_rock",false}},{{"threw_rock","You decide not to further desecrate his corpse"},{"has_stones","You don't have that"}}),
			action("check (man/body)","You rummage through his pockets and find... a key!",{{"has_key",true}},-1,{{"threw_stones",true},{"has_key",false}},{{"has_key","There's nothing else there"},{"threw_stones","You can't do that"}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself in a small clearing in the woods whera a small log cabin resides. A man wearing a helmet and grasping a sword sits on the porch, fidgeting with nervous mannerisms.",{},-1,{{"killed_man2",false}},{{"killed_man2","The man lays sprawled out in the porch, tainted with blood"}}),
			action("talk man","As you call to him his head snaps in your direction. With a shaky voice, he explains: 'We were decimated out there. Let the witch's powers not be underestimated. Out of fifteen men, I was the only to survive her onslaught of satanic magic. I will not dare to face her again, or the baron. But with no army left to fight, her reign will surely never end.'"}}),
			action("get sword","You ask for the sword, but clutching it to his chest he says: 'What could you need with this? If not I, the king's vassal could not vanquish her, what makes you think you could?'"}}),
			action("(give/show) brooch *man","You reach into your robes and present him with the shining brooch. His eyes widen and glimmer with its reflection. 'The baron sent you?' He asks, with a hint of exasperation. His mind races. At last, he thrusts the sword into your arms, 'Take this, and don't tell the baron that I'm alive"}},{{"has_sword",true}},{{"has_sword",false}},{{"has_sword","You see no need to show him the brooch again"}}),
			action("kill man sword","You draw the sword and strike the man in the chest. He keels over onto the floor, sputtering, 'God curse your soul', and dies."}},{{"killed_man2",true}},{{"killed_man",false},{"has_sword"}},{{"killed_man","He's already dead"},{"has_sword","You don't have that"}}),
			action("check (man/body)","You check his pockets and find ... a key!"}},{{"has_key2",true}},{{"has_key2",false},{"killed_man2",true}},{{"has_key2","You check his pockets and find... nothing"},{"killed_man","Nothing stands out about him"}}),
	),
	scenario(
		"",
		{
			action("look around","You find yourself inside the tiny cabin."),
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself in a desolate grave yard. In the centre of the field is the abbey, to the north, on top of which crouches a menacing gargoyle. To the left is a tombstone which appears to have been dug up. A crooked tree stands tall next to it, and the wind howls through its branches. To the right are a number of other gravestones",{},-1,{{"in_tree",false}},{{"in_tree","You see the field dotted with small gravestones. On the roof of the abbey, you see the gargoyle in all its fearsomenes. Below it are words written along the buttresses of the building"}}),
			action("look abbey","The abbey is made with modest materials, but with passionate craftsmanship. The arched door has large brass hinges, and the stone rim is marked with many spiralling and tapering designs. the roof features impressive buttresses made of finely chiseled stone",{},-1,{{"in_tree",false}},{{"in_tree","You see words engraved deeply on the roof top 'LET THE HEAVENS WEEP TO THE CALL OF JEHOVAH"}}),
			action("say jehovah","|With a pensive expression, you loudly utter the lord's name. As your lips close, the scene falls silent.|Suddenly, a flash of lightning shakes the earth. In an instant, the skies are imbued with clouds and the thick sheet of rainfall. Running, you seek shelter under the tree.| After several minutes, the storm abruptly stops. Sunlight bursts into the scene once again.",{{"said_words"}},-1,{{"said_words",false}},{{"said_words","You prefer not to invoke the wrath of the lord a second time"}}),
			action("look tombstone","The tombstone is tall and decored with wonderful arches and architectural details. Atop where the name and date would logically reside there is a thick layer of dirt. Immediately below it appears as though the ground was unearthed with great fervour.",{},-1,{{"said_words",false}},{{"said_words","look tombstone","The tombstone is tall and decored with wonderful arches and architectural details. Atop the grave you read the following: 'Here lies the wretch, GENEVIEVE of HAGATHA, ?-1220. May she rot in the deepest circle of hell alongside Judas'. Immediately below it appears as though the ground was unearthed with great fervour."}}),
			action("look tree","The tree resembles a witherig old man with an unsteady gait. A nook in its centre peers at you. Swinging in the cool breeze is a creaking lantern with an unlit candle."),
			action("look grave","These graves are more modest. Attest to the lives of many men who primarily lived in the last century. Among their names are: GALEN GARNIER ALIENOR FRANCOIS, PHILIP BOURBON II"),
			action("look hole","The approach the hole and peer into it. The extent of it is much deeper than you had thought. Down into the earth your observe claw marks along the cobble-stone walls"),
			action("*go west","",{},5),
			action("(go abbey/go north)","",{{}},11,{{"gave_shovel",true}},{{"gave_shovel","It's locked"}}),
			action("dig *up grave","|With a quick sweeping glance from left to right, you pitch the shovel and begin heaving mound upon mound of dirt from its abode, beaming with greed| After some time you here the clunking of wood against your shovel. You unearth frail a coffin, and break its latches open with relative ease. Inside you find the decomposed body of a monarch past.| He wears a fine robe, and an immensely bejewelled crown. You pry it from his skull, and leap from the earth",{{"has_crown",false}},-1,{{"has_shovel",true},{"gave_shovel",true}},{{"gave_shovel","You draw the shovel but here yelling across the field. 'Ey! Let the dead be dead!', it screams.'"},{"has_shovel","With what will you dig with?"}}),
			action("talk gravekeeper","You approach the gravekeep and inquire about the witch Hagatha. He doesn't indulge you, instead he complains about having to search for his lost shovel, whilst he should be sleeping for his night shift",{},-1,{{"gave_shovel",false}},{{"gave_shovel","He isn't here"}}),
			action("give shovel gravekeeper","He makes little more conversation, but musters up a crooked smile and grumbles with glee as he takes the shovel. He waddles back to the abbey, and you think you hear a sentiment of thanks amidst  his mumurs",{{"gave_shovel",true},{"has_shovel",false}},-1,{{"gave_shovel",false},{"has_shovel",true}},{{"has_shovel","You don't have that"},{"gave_shovel","He isn't here"}}),
			action("go hole","You begin your descent down the hole",{},99,{{"has_rope",true},{"tied_rope",true}},{{"tied_rope","You peer into the hole and find it much deeper than you had initially assumed. In fact it is far too deep to descend safely"}}),
			action("climb tree","You ascend the oaken tower.",{{"in_tree",true}},-1,{{"in_tree",false},{"gave_shovel",true}},{{"gave_shovel","As you mount yourself to climb you hear yelling across the field. 'Get outta 'there', the gravekeeper cries"},{"in_tree","You are already in the tree"}}),
			action("*go *climb descend *tree","You carefully make your way down the tree",{{"in_tree",false}},-1,{{"in_tree",true}},{{"in_tree","You are not in the tree"}}),
			action("get lantern","While clinging to a sturdy branch and with an outstretched arm, you grasp for, and at last grab the lantern",{{"has_lantern",true}},-1,{{"in_tree",true},{"has_lantern",false}},{{"has_lantern","You already have that"},{"in_tree","The lantern is far too high in the tree for you to reach it"}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself in a cramped tomb. The floor, walls, and ceiling are lined with cobblestone. An open coffin lies ahead. Marking are on the wall behind."),
			action("look coffin","The coffin is wooden, with large brass hinges. Strangely enough, there is a lock on top of the lid. Scratch marks line the surface."),
			action("look wall","The writing are in latin, but you understand the general message."),
			action("Check coffin","You look inside the coffin and find... a key headed with a small skull.",{{"has_key3",true}},{{"has_key3",false}},{{"has_key3","You look inside the coffin and find... nothing"}}),
	),
	scenario(
		"",
		{
			action("look around","The shed has bleak stone walls. On the left is a bed, where the gravekeeper sleeps. To the right is a desk"),
			action("look desk","The desk is large and has many drawers built into it. On top of it is a crumpled note with many tear marks"),
			action("read note","The note reads: 'October 12: There are many ill forces at work on these grounds. Today the heretic Hagatha's grave was unearthed in a most unnatural fashion. I saw only a struck of lightning, and not long after, she emerged from hell."),
			action("get note","You don't need it"),
			action("check drawer","Inside the drawer you find the shovel you gave him. You decide to borrow it once again",{{"has_shovel",true}},-1,{{"has_shovel",false}},{{"has_shovel","There's nothing else there"}}),
			action("check bed","The bed and its sheets are modest at best. The mattress is suspended high above the ground by its supports"),
			action("check under bed","You look under the bed and find the second half of the note. It reads: 'October 3, On the request of good duke Louis of Quelqueparte, the late king Phillip II has been buried in this small yard, on account of the civil unrest his reign bred that may stir temptations to desecrate his body, or steal the many regal ornaments his attire dons upon him"),
			action("*go south","",{{}},10)
		}
	),
	scenario(
		"",
		{
			action("flip lever","You flip the lever ON",{{"lever_on",true}},-1,{{"lever_on",false}},{{"lever_on","_next_"}}),
			action("flip lever","You flip the lever OFF",{{"lever_on",false}},-1,{{"lever_on",true}},{{"lever_on","_next_"}})
		}
	),
	scenario(
		"",
		{
			action("look around","You see three slender houses fit tightly down the lane. The one on the left has a mailbox and a fine finish. The one on the left is tattered, and the door is heavily splintered. The middle is in modest condition. On the other side of the street you a store with a sign on it. Down towards the end of the street east is the base of a large clocktower."),
			action("look houses","The residencies have a humble appearance. Thatched-roofs shelter the single story, and the windows panes are imbued with dust and grime."),
			action("go middle house",""),
			action("look sign","The sign is gone",{{}},-1,{{"fixed_clock",true}},{{"fixed_clock","The sign says: 'Store opens at noon'"}}),
			action("look tower","The tower stands some thirty meters high. is made of a smootly-finished cobblestone. The face of the clock is a marvel of calligraphic art, with arching and spiralling beams signifying and decorating the hours and the hands."),
			action("(look clock/check time)","The hands of the clock wind slowly and with the frailty of an old man",{{}},-1,{{"fixed_clock",true}},{{"fixed_clock","The time is 11:45 AM. There is no hand to count seconds, but when staring at it you find that the time passes very slowly, if at all."}}),
			action("*go (west/clocktower)","",{{}},99,{{"opened_door2",true}},{{"opened_door2","The door to the clocktower is locked"}}),
			action("*go east","",{{}},5)
		}
	),
	scenario(
		"",
		{
			action("look around","After climbing a helix of stairs, you find yourself immersed in the mechanism of the clocktower. The symphonic clicking and grinding of gears and cogs fills your eardrums. The interior is dark, save for a band of light emanating from the face of the clock. In a nest of gears directly behind the face, you spot a mallet encroached inside the machine."),
			action("*go east","",{{}},11),
			action("get mallet","You pick up the mallet",{{"has_mallet",true}},-1,{{"fixed_clock",true},{"has_mallet",false}},{{"has_mallet","You already have that"},{"fixed_clock","The mallet is too far out of reach to grasp for"}}),
			action("throw stones mallet","You heave a hefty rock at the mallet. By virtue of your throwing ability you are able to dislodge the mallet. It falls to the ground, creating a cascade of noise as it knocks against one gear to another.",{{"fixed_clock",true}},-1,{{"fixed_clock",false}},{{"fixed_clock","You already have that"}}),
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself inside the run-down house."),
		}
	),
	scenario(
		"",
		{
			action("look around","You find yourself inside the next house over."),
		}
	)
};

int scenario_num = 0;
