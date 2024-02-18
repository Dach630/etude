open Graphics;;
    
let rec loop () = loop ();;

let _ =
  open_graph "";
  set_window_title "Graphics example";
  draw_rect 50 50 300 200;
  set_color red;
  fill_rect 50 50 300 200;
  set_color blue;
  draw_rect 100 100 200 100;
  fill_rect 100 100 200 100;
  loop ()
;;
