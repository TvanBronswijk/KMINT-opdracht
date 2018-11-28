#include "kmint/main.hpp"          // voor de main loop
#include "kmint/graphics.hpp"      // kleuren en afbeeldingen
#include "kmint/map/map.hpp"       // voor kaarten
#include "kmint/math/vector2d.hpp" // voor window en app
#include "kmint/play.hpp"          // voor stage
#include "kmint/ui.hpp"            // voor window en app
#include <iostream>

#include "autonomous_agent/preceptive_actor.hpp"

using namespace kmint; // alles van libkmint bevindt zich in deze namespace

int main() {
	// een app object is nodig om
	ui::app app{};

	//  maak een venster aan
	ui::window window{ app.create_window({1024, 768}, "perceptive") };

	// maak een podium aan
	play::stage s{};

	// Plaats twee actors op het scherm
	math::vector2d center{ 512, 384 }; 
	math::vector2d begin{ 10, 10 };
	auto &my_actor = s.build_actor<perceptive_actor>(begin, true, 10, 10, 10 ,10);
	auto offset = center + math::vector2d{ 50, 50 };
	auto &my_enemy = s.build_actor<perceptive_actor>(offset, false, 0, 0.1, 0.1, 0.1);
	my_enemy.set_target(my_actor);
	// Maak een event_source aan (hieruit kun je alle events halen, zoals
	// toetsaanslagen)
	ui::events::event_source event_source{};

	// main_loop stuurt alle actors aan.
	main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.

		for (ui::events::event &e : event_source) {
			// event heeft een methode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//
			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
			e.handle_key_up([&my_actor](ui::events::key_event k) {
				switch (k.key) {
				case ui::events::key::w:
					my_actor.move({ 0, -50.0f });
					break;
				case ui::events::key::s:
					my_actor.move({ 0, 50.0f });
					break;
				case ui::events::key::a:
					my_actor.move({ -50.0f, 0 });
					break;
				case ui::events::key::d:
					my_actor.move({ 50.0f, 0 });
					break;
				default:
					break;
				}
			});
		}
	});
}

//begin main grid
//#include <iostream>
//#include "kmint/main.hpp"          // voor de main loop
//#include "kmint/graphics.hpp"      // kleuren en afbeeldingen
//#include "kmint/math/vector2d.hpp" // voor window en app
//#include "kmint/play.hpp"          // voor stage
//#include "kmint/ui.hpp"            // voor window en app
//#include "kmint/map/map.hpp"
//#include "actors/cow.hpp"
//#include "kmint/random.hpp"
//#include "actors/hare.hpp"
//#include "pathfinding/algorithm.hpp"
//
//using namespace kmint; // alles van libkmint bevindt zich in deze namespace
//
//static const char *map_description = R"graph(32 24 32
//resources/firstmap.png
//G 1 1
//C 1 1
//H 1 1
//W 0 0
//B 1 8
//
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWHGGGGGGGGGGGGGGGGGGGGGGGGHWWW
//WWWGGGGGGGGGGGGGGGGGGGGGGGGGGWWW
//WWWGGGGGGGGGGGGGBGGGGGGGGGGGGWWW
//WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWGGBGWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
//WWWGGGGGBBBBBBBGCGGGGGGGGGGGGWWW
//WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWGGBGWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
//WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
//WWWGGGGGGGGGGGGGBGGGGGGGGGGGGWWW
//WWWGGGGGGGGGGGGGGGGGGGGGGGGGGWWW
//WWWHGGGGGGGGGGGGGGGGGGGGGGGGHWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//)graph";
//
//const map::map_node &find_cow_node(const map::map_graph &graph) {
//	for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
//		if (graph[i].node_info().kind == 'C') {
//			return graph[i];
//		}
//	}
//	throw "could not find starting point";
//}
//
//void run() {
//	// een app object is nodig om
//	ui::app app{};
//
//	//  maak een venster aan
//	ui::window window{ app.create_window({1024, 768}, "hello") };
//
//	// maak een podium aan
//	play::stage s{};
//
//	// Laad een kaart
//	map::map m{ map::read_map(map_description) };
//	s.build_actor<play::background>(
//		math::size(1024, 768),
//		graphics::image{ m.background_image() });
//	s.build_actor<play::map_actor>(
//		math::vector2d{ 0.0f, 0.0f },
//		m.graph());
//
//
//	std::vector<std::reference_wrapper<item>> items_;
//
//	for (size_t i = 0; i < 10; i++) {
//		int d = random_int(0, 2);
//		if (d == 0) {
//			items_.emplace_back(s.build_actor<item>('p', "resources/pill.png", m.graph()));
//		}else
//			items_.emplace_back(s.build_actor<item>('w', "resources/weapon.png", m.graph()));
//	}
//
//	auto &my_cow = s.build_actor<cow>(m.graph(), find_cow_node(m.graph()), items_);
//	auto &my_hare = s.build_actor<hare>(m.graph());
//	my_cow.set_hare(my_hare);
//	my_hare.set_cow(my_cow);
//
//	for (std::vector<std::reference_wrapper<item>>::iterator it = items_.begin(); it != items_.end(); ++it) {
//		it->get().set_cow(my_cow);
//	}
//
//	// Maak een event_source aan (hieruit kun je alle events halen, zoals
//	// toetsaanslagen)
//	ui::events::event_source event_source{};
//
//	// main_loop stuurt alle actors aan.
//	main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
//		// gebruik dt om te kijken hoeveel tijd versterken is
//		// sinds de vorige keer dat deze lambda werd aangeroepen
//		// loop controls is een object met eigenschappen die je kunt gebruiken om de
//		// main-loop aan te sturen.
//
//		for (ui::events::event &e : event_source) {
//			// event heeft een methode handle_quit die controleert
//			// of de gebruiker de applicatie wilt sluiten, en zo ja
//			// de meegegeven functie (of lambda) aanroept om met het
//			// bijbehorende quit_event
//			//
//			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
//		}
//	});
//}
//
//int main() {
//	//run the program
//	run();
//
//	//memory leak detection
//	_CrtDumpMemoryLeaks();
//
//	return 0;
//}
// end main grid
