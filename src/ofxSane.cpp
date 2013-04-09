#include "ofxSane.h"

void printStatus(SANE_Status status) {
    cout << "status: " << sane_strstatus(status) << endl;
}

void printDevice(const SANE_Device* device) {
    cout << "device:" << endl <<
        "\tname = " << device->name << endl <<
        "\tvendor = " << device->vendor << endl <<
        "\tmodel = " << device->model << endl <<
        "\ttype = " << device->type << endl;
}

string typeToString(const SANE_Value_Type& type) {
    switch(type) {
        case SANE_TYPE_BOOL: return "bool";
        case SANE_TYPE_INT: return "int";
        case SANE_TYPE_FIXED: return "fixed";
        case SANE_TYPE_STRING: return "string";
        case SANE_TYPE_BUTTON: return "button";
        case SANE_TYPE_GROUP: return "group";
        default: return "?";
    }
}

string unitToString(const SANE_Unit& unit) {
    switch(unit) {
        case SANE_UNIT_BIT: return "bits";
        case SANE_UNIT_DPI: return "dpi";
        case SANE_UNIT_MICROSECOND: return "microseconds";
        case SANE_UNIT_MM: return "millimeters";
        case SANE_UNIT_NONE: return "unitless";
        case SANE_UNIT_PERCENT: return "percent";
        case SANE_UNIT_PIXEL: return "pixel";
        default: return "?";
    }
}

void printDescriptor(const SANE_Option_Descriptor* descriptor) {
    cout << descriptor->title << " " <<
        "(" << typeToString(descriptor->type) <<
        "/" << unitToString(descriptor->unit) << ")" <<
        "[" << descriptor->size << "] ";
    switch(descriptor->constraint_type) {
        case SANE_CONSTRAINT_NONE:
            cout << "any value";
            break;
        case SANE_CONSTRAINT_STRING_LIST:
            cout << "{string list...}";
            break;
        case SANE_CONSTRAINT_WORD_LIST:
            cout << "{word list...}";
            break;
        case SANE_CONSTRAINT_RANGE:
            const SANE_Range* range = descriptor->constraint.range;
            cout << range->min << " to " << range->max;
            if(range->quant != 0)
                cout << " in " << range->quant;
            break;
    }
    cout << endl;
}
