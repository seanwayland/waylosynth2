

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Oscillator.h"
#include "Filters.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif



Oscillator::Oscillator() {
    m_wavetype = 2;
    m_freq = 1.f;
    midi_note_number = 0;
    m_sharp = 0.f;
    srand((unsigned int)time(0));
    m_sah_last_value = 0.f;
    m_sah_current_value = (rand() / (float)RAND_MAX) * 2.f - 1.f;
    m_pitchbend = 1;
    
    
    
}

void Oscillator::setup(float sampleRate) {
    m_sampleRate = sampleRate;
    m_sampleRate = 96000;
    amp_env.SetSampleRate(96000);
    amp_env.reset();
    m_oneOverSr = 1.f / m_sampleRate;
    m_increment = m_runningPhase = 0.0f;
    m_twopi = 2.f * M_PI;
    m_oneOverPiOverTwo = 1.f / (M_PI / 2.f);
    m_srOverFour = m_sampleRate / 4.f;
    m_srOverEight = m_sampleRate / 8.f;
    m_pointer_pos = m_sah_pointer_pos = 0.f;
    SmoothData = 0.f;
    fixed_pulse_counter = 0;
    oldval = hi_pass_output = 0.f;
    modulator = 0;
    m_pitchbend = 1;
    
        // vadimFilter
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = 512;
    spec.sampleRate = sampleRate;
    spec.numChannels = 1;
    vadimFilter.prepare(spec);
    vadimFilter.reset();
    vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);

}

Oscillator::~Oscillator() {}

void Oscillator::reset() {
    m_pointer_pos = fm_phase_1 = fm_phase_2 = fm_phase_3 = m_sah_pointer_pos = 0.f;
    m_pitchbend = 1;
    amp_env.reset();
    env.gate(false);
    env.reset();
    env.gate(true);

}

void Oscillator::set_midi_note_number(int midi_note){
    midi_note_number = midi_note;
}


// This is a transition table that helps with bandlimited oscs.
float transition[1001]={-0.500003,-0.500003,-0.500023,-0.500063,-0.500121,-0.500179,-0.500259,
    -0.50036,-0.500476,-0.500591,-0.500732,-0.500893,-0.501066,-0.501239,
    -0.50144,-0.501661,-0.501891,-0.502123,-0.502382,-0.502662,-0.502949,
    -0.50324,-0.503555,-0.503895,-0.504238,-0.504587,-0.504958,-0.505356,
    -0.505754,-0.506162,-0.506589,-0.507042,-0.507495,-0.50796,-0.508444,
    -0.508951,-0.509458,-0.509979,-0.510518,-0.511079,-0.511638,-0.512213,
    -0.512808,-0.51342,-0.51403,-0.514659,-0.515307,-0.51597,-0.51663,-0.517312,
    -0.518012,-0.518724,-0.519433,-0.520166,-0.520916,-0.521675,-0.522432,
    -0.523214,-0.524013,-0.524819,-0.525624,-0.526451,-0.527298,-0.528147,
    -0.528999,-0.52987,-0.530762,-0.531654,-0.532551,-0.533464,-0.534399,
    -0.535332,-0.536271,-0.537226,-0.538202,-0.539172,-0.540152,-0.541148,
    -0.542161,-0.543168,-0.544187,-0.54522,-0.546269,-0.54731,-0.548365,
    -0.549434,-0.550516,-0.55159,-0.552679,-0.553781,-0.554893,-0.555997,
    -0.557118,-0.558252,-0.559391,-0.560524,-0.561674,-0.562836,-0.564001,
    -0.565161,-0.566336,-0.567524,-0.568712,-0.569896,-0.571095,-0.572306,
    -0.573514,-0.574721,-0.575939,-0.577171,-0.578396,-0.579622,-0.580858,
    -0.582108,-0.583348,-0.58459,-0.585842,-0.587106,-0.588358,-0.589614,
    -0.590879,-0.592154,-0.593415,-0.594682,-0.595957,-0.59724,-0.598507,
    -0.599782,-0.601064,-0.602351,-0.603623,-0.604902,-0.606189,-0.607476,
    -0.60875,-0.610032,-0.611319,-0.612605,-0.613877,-0.615157,-0.616443,
    -0.617723,-0.618992,-0.620268,-0.621548,-0.62282,-0.624083,-0.62535,
    -0.626622,-0.627882,-0.629135,-0.630391,-0.631652,-0.632898,-0.634138,
    -0.63538,-0.636626,-0.637854,-0.639078,-0.640304,-0.641531,-0.642739,
    -0.643943,-0.645149,-0.646355,-0.647538,-0.64872,-0.649903,-0.651084,
    -0.652241,-0.653397,-0.654553,-0.655705,-0.656834,-0.657961,-0.659087,
    -0.660206,-0.661304,-0.662399,-0.663492,-0.664575,-0.665639,-0.666699,
    -0.667756,-0.6688,-0.669827,-0.670849,-0.671866,-0.672868,-0.673854,
    -0.674835,-0.675811,-0.676767,-0.677709,-0.678646,-0.679576,-0.680484,
    -0.68138,-0.682269,-0.683151,-0.684008,-0.684854,-0.685693,-0.686524,
    -0.687327,-0.688119,-0.688905,-0.689682,-0.690428,-0.691164,-0.691893,
    -0.692613,-0.6933,-0.693978,-0.694647,-0.695305,-0.695932,-0.696549,
    -0.697156,-0.697748,-0.698313,-0.698865,-0.699407,-0.699932,-0.700431,
    -0.700917,-0.701391,-0.701845,-0.702276,-0.702693,-0.703097,-0.703478,
    -0.703837,-0.704183,-0.704514,-0.704819,-0.705105,-0.705378,-0.705633,
    -0.70586,-0.706069,-0.706265,-0.706444,-0.706591,-0.706721,-0.706837,
    -0.706938,-0.707003,-0.707051,-0.707086,-0.707106,-0.707086,-0.707051,
    -0.707001,-0.706935,-0.706832,-0.706711,-0.706576,-0.706421,-0.706233,
    -0.706025,-0.705802,-0.705557,-0.705282,-0.704984,-0.704671,-0.704334,
    -0.703969,-0.703582,-0.703176,-0.702746,-0.702288,-0.70181,-0.701312,
    -0.700785,-0.700234,-0.699664,-0.69907,-0.698447,-0.6978,-0.697135,
    -0.696446,-0.695725,-0.694981,-0.694219,-0.693435,-0.692613,-0.691771,
    -0.690911,-0.69003,-0.689108,-0.688166,-0.687206,-0.686227,-0.685204,
    -0.684162,-0.683101,-0.682019,-0.680898,-0.679755,-0.678592,-0.677407,
    -0.676187,-0.674941,-0.673676,-0.672386,-0.671066,-0.669718,-0.66835,
    -0.666955,-0.665532,-0.664083,-0.662611,-0.661112,-0.659585,-0.658035,
    -0.656459,-0.654854,-0.653223,-0.651572,-0.649892,-0.648181,-0.646446,
    -0.644691,-0.642909,-0.641093,-0.639253,-0.637393,-0.63551,-0.633588,
    -0.631644,-0.62968,-0.627695,-0.625668,-0.623621,-0.621553,-0.619464,
    -0.617334,-0.615183,-0.613011,-0.610817,-0.608587,-0.606333,-0.604058,
    -0.60176,-0.599429,-0.597072,-0.594695,-0.592293,-0.589862,-0.587404,
    -0.584925,-0.58242,-0.579888,-0.577331,-0.574751,-0.572145,-0.569512,
    -0.566858,-0.564178,-0.561471,-0.558739,-0.555988,-0.553209,-0.550402,
    -0.547572,-0.544723,-0.54185,-0.538944,-0.536018,-0.533072,-0.530105,
    -0.527103,-0.524081,-0.52104,-0.51798,-0.514883,-0.511767,-0.508633,
    -0.505479,-0.502291,-0.499083,-0.495857,-0.492611,-0.489335,-0.486037,
    -0.48272,-0.479384,-0.476021,-0.472634,-0.46923,-0.465805,-0.462356,
    -0.458884,-0.455394,-0.451882,-0.448348,-0.444795,-0.44122,-0.437624,
    -0.434008,-0.430374,-0.426718,-0.423041,-0.419344,-0.415631,-0.411897,
    -0.40814,-0.404365,-0.400575,-0.396766,-0.392933,-0.389082,-0.385217,
    -0.381336,-0.377428,-0.373505,-0.369568,-0.365616,-0.361638,-0.357645,
    -0.353638,-0.349617,-0.345572,-0.341512,-0.337438,-0.33335,-0.329242,
    -0.325118,-0.32098,-0.316829,-0.31266,-0.308474,-0.304276,-0.300063,
    -0.295836,-0.291593,-0.287337,-0.283067,-0.278783,-0.274487,-0.270176,
    -0.265852,-0.261515,-0.257168,-0.252806,-0.248431,-0.244045,-0.239649,
    -0.23524,-0.230817,-0.226385,-0.221943,-0.21749,-0.213024,-0.208548,
    -0.204064,-0.199571,-0.195064,-0.190549,-0.186026,-0.181495,-0.176952,
    -0.1724,-0.167842,-0.163277,-0.1587,-0.154117,-0.149527,-0.14493,-0.140325,
    -0.135712,-0.131094,-0.12647,-0.121839,-0.117201,-0.112559,-0.10791,
    -0.103257,-0.0985979,-0.0939343,-0.0892662,-0.0845935,-0.079917,-0.0752362,
    -0.0705516,-0.0658635,-0.0611729,-0.0564786,-0.0517814,-0.0470818,-0.0423802,
    -0.0376765,-0.0329703,-0.0282629,-0.0235542,-0.0188445,-0.0141335,-0.00942183,
    -0.00470983,2.41979e-06,0.00471481,0.00942681,0.0141384,0.0188494,0.023559,
    0.028268,0.0329754,0.0376813,0.0423851,0.0470868,0.0517863,0.0564836,
    0.0611777,0.0658683,0.0705566,0.0752412,0.0799218,0.0845982,0.0892712,
    0.0939393,0.0986028,0.103262,0.107915,0.112563,0.117206,0.121844,0.126475,
    0.131099,0.135717,0.14033,0.144935,0.149531,0.154122,0.158705,0.163281,
    0.167847,0.172405,0.176956,0.1815,0.18603,0.190553,0.195069,0.199576,
    0.204068,0.208552,0.213028,0.217495,0.221947,0.226389,0.230822,0.235245,
    0.239653,0.244049,0.248436,0.252811,0.257173,0.26152,0.265857,0.270181,
    0.274491,0.278788,0.283071,0.287341,0.291597,0.29584,0.300068,0.30428,
    0.308478,0.312664,0.316833,0.320984,0.325122,0.329246,0.333354,0.337442,
    0.341516,0.345576,0.34962,0.353642,0.357649,0.361642,0.36562,0.369572,
    0.373509,0.377432,0.38134,0.385221,0.389086,0.392936,0.39677,0.400579,
    0.404369,0.408143,0.4119,0.415634,0.419347,0.423044,0.426721,0.430377,
    0.434011,0.437627,0.441223,0.444798,0.448351,0.451885,0.455397,0.458887,
    0.462359,0.465807,0.469232,0.472637,0.476024,0.479386,0.482723,0.486039,
    0.489338,0.492613,0.49586,0.499086,0.502294,0.505481,0.508635,0.511769,
    0.514885,0.517982,0.521042,0.524083,0.527105,0.530107,0.533074,0.53602,
    0.538946,0.541851,0.544725,0.547574,0.550404,0.553211,0.555989,0.55874,
    0.561472,0.564179,0.566859,0.569514,0.572146,0.574753,0.577332,0.579889,
    0.582421,0.584926,0.587405,0.589863,0.592294,0.594696,0.597073,0.59943,
    0.60176,0.604059,0.606333,0.608588,0.610818,0.613012,0.615183,0.617335,
    0.619464,0.621553,0.623621,0.625669,0.627696,0.629681,0.631645,0.633588,
    0.63551,0.637393,0.639253,0.641093,0.642909,0.644691,0.646446,0.648181,
    0.649892,0.651572,0.653223,0.654854,0.656459,0.658035,0.659585,0.661112,
    0.662611,0.664083,0.665532,0.666955,0.66835,0.669718,0.671066,0.672386,
    0.673676,0.674941,0.676187,0.677407,0.678592,0.679755,0.680898,0.682019,
    0.683101,0.684162,0.685204,0.686227,0.687206,0.688166,0.689108,0.69003,
    0.690911,0.691771,0.692613,0.693435,0.694219,0.694981,0.695725,0.696447,
    0.697135,0.6978,0.698447,0.69907,0.699664,0.700234,0.700786,0.701312,
    0.70181,0.702288,0.702746,0.703177,0.703582,0.703969,0.704334,0.704671,
    0.704984,0.705282,0.705557,0.705802,0.706025,0.706233,0.706422,0.706576,
    0.706712,0.706832,0.706936,0.707002,0.707051,0.707086,0.707106,0.707086,
    0.707051,0.707003,0.706939,0.706838,0.706721,0.706592,0.706445,0.706265,
    0.70607,0.705861,0.705634,0.705378,0.705105,0.70482,0.704515,0.704184,
    0.703837,0.703478,0.703097,0.702694,0.702276,0.701846,0.701392,0.700917,
    0.700432,0.699932,0.699408,0.698866,0.698314,0.697749,0.697156,0.696549,
    0.695933,0.695305,0.694648,0.693979,0.693301,0.692613,0.691894,0.691165,
    0.690428,0.689683,0.688905,0.68812,0.687327,0.686525,0.685693,0.684854,
    0.684009,0.683152,0.68227,0.68138,0.680485,0.679577,0.678647,0.67771,
    0.676768,0.675811,0.674836,0.673855,0.672869,0.671867,0.670849,0.669827,
    0.668801,0.667757,0.6667,0.66564,0.664576,0.663493,0.6624,0.661305,
    0.660207,0.659088,0.657962,0.656834,0.655705,0.654553,0.653398,0.652241,
    0.651085,0.649903,0.648721,0.647539,0.646356,0.645149,0.643944,0.642739,
    0.641532,0.640304,0.639079,0.637855,0.636626,0.635381,0.634139,0.632899,
    0.631652,0.630392,0.629136,0.627883,0.626622,0.62535,0.624083,0.62282,
    0.621548,0.620268,0.618993,0.617724,0.616443,0.615158,0.613878,0.612605,
    0.61132,0.610032,0.608751,0.607477,0.606189,0.604903,0.603623,0.602351,
    0.601065,0.599782,0.598508,0.59724,0.595957,0.594682,0.593415,0.592154,
    0.59088,0.589615,0.588359,0.587106,0.585843,0.584591,0.583349,0.582108,
    0.580859,0.579623,0.578397,0.577172,0.575939,0.574721,0.573515,0.572307,
    0.571095,0.569897,0.568713,0.567525,0.566337,0.565161,0.564002,0.562837,
    0.561674,0.560525,0.559392,0.558252,0.557119,0.555998,0.554893,0.553782,
    0.552679,0.55159,0.550516,0.549434,0.548365,0.54731,0.546269,0.54522,
    0.544187,0.543168,0.542161,0.541148,0.540153,0.539173,0.538202,0.537226,
    0.536271,0.535332,0.5344,0.533464,0.532551,0.531654,0.530762,0.52987,
    0.528999,0.528147,0.527298,0.526451,0.525624,0.524819,0.524014,0.523214,
    0.522432,0.521675,0.520916,0.520166,0.519433,0.518724,0.518012,0.517312,
    0.51663,0.51597,0.515307,0.51466,0.51403,0.51342,0.512808,0.512213,
    0.511638,0.511079,0.510518,0.509979,0.509458,0.508951,0.508444,0.50796,
    0.507495,0.507042,0.506589,0.506162,0.505754,0.505356,0.504958,0.504587,
    0.504237,0.503895,0.503555,0.50324,0.502949,0.502662,0.502382,0.502123,
    0.501891,0.501661,0.50144,0.501239,0.501066,0.500893,0.500732,0.500591,
    0.500476,0.50036,0.500259,0.500179,0.500121,0.500063,0.500023,0.500003,0.500003};


// patrice functions

float Oscillator::b(float x, float a){
    if (x < a){
        float x_over_a_minus_1 = (x/a) -1.0;
        float x_over_a_minus_1_squared = x_over_a_minus_1 * x_over_a_minus_1 ;
        return  -1.0* x_over_a_minus_1_squared;
    }
    else if (x > ( 1.0 -a )){
        float x_minus_1_over_a = (x-1.0)/a;
        float root_val = 1.0 + x_minus_1_over_a;
        return root_val*root_val;
    }
    else{
        return 0.0;
    }
    
}

float Oscillator::s(float input){
    return abs(fmod(input, 1.0));
}


float Oscillator::r0(float input, float w){
    if (s(input)< w){
        return 1.0;}
    else{
        return -1.0;
        }
        
    }

// r1(x) = r0(x) + b(s(x)) - b(s(x-w))
float Oscillator::r1(float input, float a, float w){
    b_s_x = b(s(input),a);
    b_s_x_minus_w = b(s(input-w),a);
    return r0(input,w) + b_s_x - b_s_x_minus_w;
}


float Oscillator::_clip(float x) {
    if (x < 0.f) {
        x += 1.f;
    } else if (x >= 1.f) {
        x -= 1.f;
    }
    return x;
}


void Oscillator::setWavetype(int type) {
    if (type != m_wavetype) {
        type = type < 0 ? 0 : type > 9 ? 9 : type;
        m_wavetype = type;
    }
}

void Oscillator::setFreq(float freq) {
    m_freq = freq < 0.00001f ? 0.00001f : freq > m_srOverFour ? m_srOverFour : freq;
    m_increment = m_freq / m_sampleRate;
}

void Oscillator::setSharp(float sharp) {
    m_sharp = sharp < 0.f ? 0.f : sharp > 1.f ? 1.f : sharp;
}

void Oscillator::setMod(float mod) {
    m_mod = mod < 0.f ? 0.f : mod > 1.f ? 1.f : mod;
}


void Oscillator::set_note_velocity(float note_velocity){
    m_note_velocity = note_velocity;
}


void Oscillator::setPitchBend(float pitchWheelPos){
    
    if( (m_note_velocity > 0.5 && (pedal_steel == 1) ) || (pedal_steel == 0) ){
        if (pitchWheelPos > 8192){
            auto val = pitchWheelPos - 8192;
            m_pitchbend = 1 + (val/10000);
        }
        else {
            auto val = 8192 - pitchWheelPos;
            m_pitchbend = 1 - val/8192;
            
        }
        
        if (m_pitchbend < 0.5){
            m_pitchbend = 0.5;
        }
        
        if (m_pitchbend > 1.5){
            m_pitchbend = 1.5;
        }}
    else{ m_pitchbend = 1.0;}

      
}
   
float Oscillator::process() {
    float v1 = 0.f, v2 = 0.f, pointer = 0.f, numh = 0.f, pos = 0.f;
    float inc2 = 0.f, fade = 0.f, value = 0.f, maxHarms = 0.f;
    float oldvalue = old_x_value = old_y_value = 0.0;
    float key_adjust = 0.0f;
    m_feedback = 0.0f;
    
    

    switch (m_wavetype) {
            // Sine with feedback attenuated with pitch
        case 0:
            
            
            //m_feedback = 0.93 - (0.0004*m_freq);
            
            //            if (m_sharp > 0.68){m_sharp = 0.68;}
            //            m_feedback = (m_sharp+0.4) - (0.0004*m_freq);
            m_feedback = (m_sharp + m_note_velocity/5) - (0.0005*m_freq);
            
            //m_feedback = 0.5;
            //vadimFilter.setResonance(m_mod*2);
            
            
            //            if (m_feedback > 1.0 || m_feedback < 0.1){
            //                m_feedback = 0.6;
            //            }
            

            
            
        {modulator = sinf(m_twopi * m_pointer_pos + (prev_value*m_feedback*0.8));
            prev_value = modulator;
            
            //value = sinf(0.25*10*(modulator) + m_twopi * m_pointer_pos + (old_value*m_feedback*0.8));
            value = sinf((m_mod+ (m_note_velocity/5))*10*(modulator) + m_twopi * m_pointer_pos + (old_value*m_feedback*0.8));
            vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            vadimFilter.setCutoffFrequency(3000*m_sharp + value*1000*m_sharp);
            value = vadimFilter.processSample(1, value);
            old_value = value;
            
            
            break;}
            

    
            
            // band limited pulse width waylo belangeo
        case 1:
            
        {
            pulse_width = m_mod;
            phase1 = m_pointer_pos + 0.5 * pulse_width;
            phase2 = m_pointer_pos - 0.5 * pulse_width;
            
            maxHarms = 3*(m_srOverFour / m_freq);
            // modified to allow m_sharp to change wave shape
            //numh = m_sharp * 80.f + 4.f;
            numh =  80.f + 4.f;
            
            if (numh > maxHarms)
                numh = maxHarms;
            pos = phase1 + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value1 = -(pos - tanhf(numh * pos) / tanhf(numh));
            
            pos = phase2 + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value2 = -(pos - tanhf(numh * pos) / tanhf(numh));
            
            value = value1 - (m_sharp*value2);
            //value = hipass(value);
            
            
            break;}
            // dx7 2 op
            
        case 2:
            
            
        {
            m_feedback_x = 6.0;
            m_feedback_y = 8.0;
            float x = m_twopi * m_pointer_pos;
            float y = m_twopi * m_pointer_pos;
            float A1 = 1.0;
            float f1 = 1.0;
            float A2 = m_mod*10;
            float f2 = 1.0;
            value = sin(y + A2 * sin(x + m_feedback*old_x_value) + old_y_value);
            old_x_value = sin(x);
            old_y_value = sin(y);
            //value = hipass(value);
            break;}
            // Saw
            
        case 3:
            
        {maxHarms = 4*m_srOverFour / m_freq;
            numh = m_sharp * 100.f + 4.f;
            if (numh > maxHarms)
                numh = maxHarms;
            pos = m_pointer_pos + 0.5f;
            if (pos >= 1.f)
                pos -= 1.f;
            pos = pos * 2.f - 1.f;
            value = -(pos - tanhf(numh * pos) / tanhf(numh));
            
            //value = hipass(value);
            
            
            
            break;}
            
            // Ramp
            // attempt at saw like "fixed pulse"
            // oscillator called P2 on page 21 https://mirm.ru/upload/iblock/cd0/Nord%20Lead%20A1,%20A1R%20(EN).pdf
            
        case 4:
            
        {
            if(m_mod < 0.001){m_mod = 0.001;}
        
        if (fixed_pulse_counter < 0.1f){
            value = m_mod*10.f * fixed_pulse_counter;
        }
        else{
            value = 2.0f + (-10.f * fixed_pulse_counter*m_mod);
        }
            
            if (value < 0){
                value = 0;
            }
            
            if (m_pointer_pos < 0.1)
            {
                fixed_pulse_counter = 0.0f;
            }
            
            
            env.setAttackRate(m_sampleRate/15);
            env.setDecayRate(m_sampleRate*1.2);
            env.setReleaseRate(m_sampleRate);
            env.setSustainLevel(0.1);
            env.setTargetRatioA(0.1);
            env.setTargetRatioDR(2.0);
            float env_value = env.getOutput();
            
            float filter_cutoff = m_sharp*(env_value*8000+ 300);
            float filter_resonance = 0.1f;
            
            filter.setMultimode(1.0f);
            filter.setResonance(filter_resonance);
            value = filter.Apply4Pole(value,filter_cutoff);
            
            if (m_freq > 0){
                vadimFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
                vadimFilter.setCutoffFrequency(m_freq - m_freq/20);
                value = vadimFilter.processSample(1, value);}
            
            
        break;}
            // pulse like 
        case 5:
            
        {
            
//            //m_feedback = 0.93 - (0.0004*m_freq);
//            if(m_sharp<0.3){
//                m_sharp = 0.3;
//            }
//
//            m_feedback = m_sharp*0.95 - (0.0004*m_freq);
//            if (m_feedback > 1.0 || m_feedback < 0.1){
//                m_feedback = 0.6;
//            }
//
//            value = sinf(m_twopi * m_pointer_pos + (old_value*m_feedback));
//            old_value = value;
//            //value = hipass(value);
            
              float f = 2 + m_mod*20;
              if (f > 20) { f = 20;}
              float j = (f*m_pointer_pos)-1;
              float x = (-1*pow(j,5.6)) + 1;
              if (isnan(x)){x=0.0;}
              if (x < 0) { x = 0.0 ;}
              if (x>1 ){ x = 1.0 ;}
            
              float filter_cutoff = m_sharp*5000;
              float filter_resonance = 0.05f;
              filter.setMultimode(1.0f);
              filter.setResonance(filter_resonance);
              value = filter.Apply3Pole(x,filter_cutoff);
             

            break;
            
        }
        
            // 2 op fm with feedback
        case 6:
            
        {
            float x = m_twopi * m_pointer_pos;
            float A1 = 1.0;
            float f1 = 1.0;
            float A2 = 3.5;
            float f2 = 1.0;
            value = A1 * sin(f1*x + 10*m_mod * sin(f2*x) + (old_value*m_sharp))  ;
            old_value = value;
            prev_value = value;
            value = (value + prev_value)/2;
            //value = hipass(value);
            break;}
            
            // waylo tan function with low pass
        case 7:
            
        {
            
            float pw = 3*(m_mod+ 0.3f);
            value = tanhf(m_twopi*sin(pw*M_PI*m_pointer_pos));
            if (m_pointer_pos>(1/pw)){
                value = 0;
            }
            float filter_cutoff = m_sharp*5000;
            float filter_resonance = 0.05f;
            filter.setMultimode(1.0f);
            filter.setResonance(filter_resonance);
            value = filter.Apply4Pole(value,filter_cutoff);
            break;}
            
            // waylo tan function with low pass
        case 8:
            
        {
            
            

             // potentially buggy max saw 
//            float temp=(8820.22/m_freq)*m_pointer_pos;
//            if (temp<0.0) {
//                temp=0.0;
//            }
//            if (temp>0.5) {
//                temp=0.5;
//            }
//            temp*=1000.0f;
//            temp+=500.0f;
//            float remainder = temp - floor(temp);
//            value = (float)((1.0f-remainder) * transition[(long)temp] + remainder * transition[1+(long)temp]) - m_pointer_pos;
//
//            float filter_cutoff = m_sharp*5000;
//            float filter_resonance = 0.05f;
//            filter.setMultimode(1.0f);
//            filter.setResonance(filter_resonance);
//            value = filter.Apply4Pole(value,filter_cutoff);
            
            
            
            if (m_mod > 0.8){m_mod = 0.8f;}
            if (m_mod < 0.2){m_mod = 0.2f;}
            float a = 0.15- (m_sharp / 10.0);
            float w = m_mod + (m_note_velocity/10);
            value = r1(m_pointer_pos, a,  w);
            
            
            env.setAttackRate(m_sampleRate/20);
            env.setDecayRate(m_sampleRate*0.8);
            env.setReleaseRate(m_sampleRate*0.7);
            env.setSustainLevel(0.1);
            env.setTargetRatioA(0.1);
            env.setTargetRatioDR(2.0);
            float env_value = env.getOutput();
            
            float filter_cutoff = m_sharp*(env_value*8000+ 300);
            float filter_resonance = 0.1f;
            filter.setMultimode(1.0f);
            filter.setResonance(filter_resonance);
            value = filter.Apply4Pole(value,filter_cutoff);

            

            
            
            
            
            
            
            
            
            
            // waylo tan
//            if (m_mod > 0.8){m_mod = 0.8f;}
//            if (m_mod < 0.2){m_mod = 0.2f;}
//            float a = 0.15- (m_sharp / 10.0);
//            float w = m_mod + (m_note_velocity/10);
//            value = r1(m_pointer_pos, a,  w);
            break;
        }
            
        case 9:
        {
            
            env.setAttackRate(m_sampleRate*3);
            env.setDecayRate(m_sampleRate*4);
            env.setReleaseRate(m_sampleRate*4);
            env.setSustainLevel(0.2);
            env.setTargetRatioA(0.5);
            env.setTargetRatioDR(1.0);
            float env_value = env.getOutput();            // reface DX
            // operator 3 is 2 all others are 1
            // 4 -> 3 -> 1
            // 2 -> 1
            // operators 1 and 3 are mixed in the output
            float op1_level = 117/127;
            float op2_level = 101/127;
            float op3_level = 84/127;
            float op4_level = 96/127;
            
            float op1_fdbk = 48*2/127;
            float op2_fdbk = 33*2/127;
            float op3_fdbk = 46*2/127;
            float op4_fdbk = 25*2/127;
            
            //// dx7 2 op
            //
            //// f you have a signal x(t) = sin(w*t) and a modulation signal f(t) then:
            //// x(t) = sin(w*t + f(t))
            //
            ////  carrierPhase += carrierFreq
            //// carrier=sin(carrierPhase + modIndex*modulatorOut).
            //
            //// value = sin((phase + modulation)*TWO_PI);
  
            
            
           // if(m_sharp > 0.65){m_sharp = 0.65;}
            m_feedback = (m_sharp+0.4) - (0.0004*m_freq);
            if (m_feedback > 1.0){m_feedback = 0.9;}
            if (m_feedback < 0.1){m_feedback = 0.1;}
            
            if (midi_note_number > 0 &&   !(isnan(midi_note_number ))){ m_mod = m_mod + 1/midi_note_number;};
            

            
            
            // operator 4
            float fm_value_4 = sinf(m_twopi*fm_phase_2 + m_feedback*old_value_4);
            old_value_4 = 0.7*fm_value_4;
            
            
            // operator 3
            float fm_value_3 = sinf(m_twopi*fm_phase_3 + m_feedback*old_value_3 + (m_note_velocity)*m_mod*10*fm_value_4);
            old_value_3 = 0.6*fm_value_3;

    
            // operator 2
            float fm_value_2 = sinf(m_twopi*fm_phase_2 + m_feedback*old_value_2);
            old_value_2 =  0.8*fm_value_2;
            //value = (fm_value_1 + old_value)/2;
            //value = fm_value_2;

            
            // operator 1
            float fm_value_1 = sinf(m_twopi*fm_phase_2 + m_feedback*old_value_1 + env_value*(m_note_velocity)*m_mod*10*fm_value_2 + (m_note_velocity)*m_mod*10*fm_value_3);
            old_value_1 = fm_value_1;
            //value = (fm_value_1 + old_value)/2;
            value = fm_value_1 + fm_value_3;
            fm_phase_2 += m_pitchbend* m_freq * m_oneOverSr;
            fm_phase_2 = _clip(m_pointer_pos);
            fm_phase_3 += m_pitchbend* m_freq*2 * m_oneOverSr;
            fm_phase_3 = _clip(m_pointer_pos);
            
            
            
            
            
            break;
        }
    }
    
    if (m_wavetype < 10) {

        m_pointer_pos += m_pitchbend* m_freq * m_oneOverSr;
        m_pointer_pos = _clip(m_pointer_pos);
        fixed_pulse_counter += 11000 * m_oneOverSr;
        //fixed_pulse_counter = _clip(fixed_pulse_counter);
        env.process();
        
    }

    return value;
}
