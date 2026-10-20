#pragma once
// Fields a recomposition draw inherits from the song it redraws. Kept apart
// from yue2-pipeline.h (and templated on the state type) so a standalone test
// can check it without ggml or models. A redraw that drops abc_given / abc_text
// fails the lyric_schedule guard ("needs a supplied score"), issue #234.
template <class S> void yue2_recompose_copy(S & ds, const S & sg) {
    ds.src_song   = sg.src_song;
    ds.style      = sg.style;
    ds.lyrics     = sg.lyrics;
    ds.abc_text   = sg.abc_text;
    ds.abc_given  = sg.abc_given;
    ds.abc_ids    = sg.abc_ids;
    ds.score_abc  = sg.score_abc;
    ds.noise_seed = sg.noise_seed;
}
