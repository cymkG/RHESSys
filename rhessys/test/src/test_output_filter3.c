#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "output_filter.h"

OutputFilter *parse(const char* input);

void test_output_filter3() {
	OutputFilter *filter = parse("test/fixtures/filter3.yml");

	g_assert(filter->next == NULL);
	// Verify output section of filter
	g_assert(filter->output != NULL);
	g_assert(filter->output->timestep == TIMESTEP_DAILY);
	g_assert(filter->output->format == OUTPUT_TYPE_CSV);
	int cmp = strcmp(filter->output->path, "output/fire-project-1");
	g_assert(cmp == 0);
	cmp = strcmp(filter->output->filename, "scenario-abc1");
	g_assert(cmp == 0);
	// Verify patch section of filter
	// IDs
	OutputFilterPatch *p1 = filter->patches;
	g_assert(p1->output_patch_type == ALL_PATCHES);
	g_assert(p1->next == NULL);
	// Variables
	OutputFilterVariable *v1 = filter->variables;
	g_assert(v1->variable_type == NAMED);
	cmp = strcmp(v1->name, "water_balance");
	g_assert(cmp == 0);
	OutputFilterVariable *v2 = v1->next;
	g_assert(v1->variable_type == NAMED);
	cmp = strcmp(v1->name, "Qout");
	OutputFilterVariable *v3 = v2->next;
	g_assert(v3->variable_type == NAMED);
	cmp = strcmp(v3->name, "Qin");
	g_assert(v3->next == NULL);

	free(filter);
}

int main(int argc, char **argv) {
	g_test_init(&argc, &argv, NULL );
	g_test_add_func("/set1/test output_filter3", test_output_filter3);
	return g_test_run();
}
