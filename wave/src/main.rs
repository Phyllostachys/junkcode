use rand::distributions::{Distribution, Standard};
use rand::Rng;
use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use sdl2::pixels::{Color, PixelFormatEnum};
use std::time::Duration;

const RENDER_X: usize = 32;
const RENDER_Y: usize = 32;

#[repr(C)]
#[derive(Default, Copy, Clone, Debug)]
struct Pixel {
    alpha: u8,
    blue: u8,
    green: u8,
    red: u8,
}

impl Distribution<Pixel> for Standard {
    fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> Pixel {
        Pixel {
            alpha: 0xFF,
            blue: rng.gen(),
            green: rng.gen(),
            red: rng.gen(),
        }
    }
}

fn main() -> Result<(), String> {
    let sdl_context = sdl2::init()?;
    let video_subsystem = sdl_context.video()?;
    let timer_subsystem = sdl_context.timer()?;

    let window = video_subsystem
        .window("wave", 800, 600)
        .position_centered()
        .build()
        .map_err(|err| err.to_string())?;

    let mut canvas = window
        .into_canvas()
        .present_vsync()
        .build()
        .map_err(|err| err.to_string())?;
    canvas.set_draw_color(Color::RGBA(10, 10, 10, 0xFF));
    canvas.clear();
    canvas.present();

    let mut buffer: Vec<Pixel> = Vec::new();
    buffer.resize(RENDER_X * RENDER_Y, Pixel::default());

    let texture_creator = canvas.texture_creator();
    let mut texture = texture_creator
        .create_texture_streaming(PixelFormatEnum::RGBA8888, RENDER_X as u32, RENDER_Y as u32)
        .map_err(|err| err.to_string())?;

    let mut start = timer_subsystem.ticks();
    let mut quit = false;
    let mut event_pump = sdl_context.event_pump()?;
    while !quit {
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit { .. }
                | Event::KeyDown {
                    keycode: Some(Keycode::Escape),
                    ..
                } => quit = true,

                // skip mouse motion intentionally because of the verbose it might cause.
                Event::MouseMotion { .. } => {}

                e => {
                    // println!("{e:?}");
                }
            }
        }

        canvas.clear();
        let now = timer_subsystem.ticks();
        let diff = (now - start) as f64 / 1000.0;
        if diff > 0.016 {
            start = now;

            let dt = now;
            update(buffer.as_mut_slice(), RENDER_Y, RENDER_Y, dt as usize);
            texture
                .update(
                    None,
                    unsafe { std::mem::transmute(buffer.as_mut_slice()) },
                    RENDER_X * 4,
                )
                .map_err(|err| err.to_string())?;
            canvas.copy(&texture, None, None)?;
        }
        canvas.present();
        std::thread::sleep(Duration::new(0, 1_000_000_000u32 / 30));
    }
    Ok(())
}

fn wave(x: usize, y: usize, width: usize, height: usize, time: usize) -> Pixel {
    let u = x as f64 / width as f64;
    let v = y as f64 / height as f64;
    let t = time as f64 / 5000.0;

    let red = 0.5 + 0.5 * (t + u + 0f64).cos();
    let green = 0.5 + 0.5 * (t + v + 2f64).cos();
    let blue = 0.5 + 0.5 * (t + u + 4f64).cos();

    Pixel {
        alpha: 0xFF,
        blue: (255.0 * blue) as u8,
        green: (255.0 * green) as u8,
        red: (255.0 * red) as u8,
    }
}

fn update(buffer: &mut [Pixel], width: usize, height: usize, time: usize) {
    for y in 0..height {
        for x in 0..width {
            // if time % 10000 > 5000 {
            buffer[width * y + x] = wave(x, y, width, height, time);
            // } else {
            //     buffer[width * y + x] = rand::random();
            // }
        }
    }
}
