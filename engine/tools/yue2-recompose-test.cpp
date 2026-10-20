// Issue #234: a recomposed draw must keep the supplied score. No GPU, no models.
#include "yue2/yue2-recompose.h"
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
struct S {
    int src_song = 0; std::string style, lyrics, abc_text; bool abc_given = false;
    std::vector<int32_t> abc_ids; std::string score_abc; uint64_t noise_seed = 0;
};
int main() {
    S sg; sg.src_song = 2; sg.style = "rock"; sg.lyrics = "[verse]"; sg.abc_text = "X:1\nK:C\nCDEF|";
    sg.abc_given = true; sg.abc_ids = {1, 2, 3}; sg.score_abc = sg.abc_text; sg.noise_seed = 7;
    S ds; yue2_recompose_copy(ds, sg);
    int fail = 0;
    if (!ds.abc_given) { printf("FAIL abc_given=%d (want 1)\n", (int) ds.abc_given); fail++; }
    if (ds.abc_text != sg.abc_text) { printf("FAIL abc_text len=%zu (want %zu)\n", ds.abc_text.size(), sg.abc_text.size()); fail++; }
    if (ds.abc_ids != sg.abc_ids || ds.style != sg.style || ds.lyrics != sg.lyrics || ds.src_song != 2 || ds.noise_seed != 7) { printf("FAIL other fields\n"); fail++; }
    // the guard yue2-pipeline.h applies to songs[0] before a lyric_schedule run
    const char * why = !ds.abc_given ? "needs a supplied score (abc)" : nullptr;
    printf("guard: %s\n", why ? why : "ok");
    printf(fail ? "yue2-recompose-test: FAIL (%d)\n" : "yue2-recompose-test: PASS\n", fail);
    return fail ? 1 : 0;
}
