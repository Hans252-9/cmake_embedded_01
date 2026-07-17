#include "temperature_filter.h"

#include "app_config.h"

static int16_t samples[APP_TEMPERATURE_FILTER_SAMPLE_COUNT];
static uint16_t sample_index;
static uint16_t sample_count;
static int32_t sample_sum;
static int16_t filtered_value;

void temperature_filter_init(void)
{
    uint16_t index;

    for (index = 0U; index < APP_TEMPERATURE_FILTER_SAMPLE_COUNT; ++index) {
        samples[index] = 0;
    }

    sample_index = 0U;
    sample_count = 0U;
    sample_sum = 0;
    filtered_value = 0;
}

int16_t temperature_filter_update(int16_t sample)
{
    if (sample_count < APP_TEMPERATURE_FILTER_SAMPLE_COUNT) {
        ++sample_count;
    } else {
        sample_sum -= samples[sample_index];
    }

    samples[sample_index] = sample;
    sample_sum += sample;
    ++sample_index;

    if (sample_index >= APP_TEMPERATURE_FILTER_SAMPLE_COUNT) {
        sample_index = 0U;
    }

    filtered_value = (int16_t)(sample_sum / (int32_t)sample_count);
    return filtered_value;
}

int16_t temperature_filter_get_value(void)
{
    return filtered_value;
}
