#ifndef _ESBLE_ATT_H_
#define _ESBLE_ATT_H_

#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/// Macro used to convert CPU integer define to LSB first 16-bits UUID
#define ESBLE_ATT_UUID_16(uuid)                          (uuid)

/// Invalid attribute handle
#define ESBLE_ATT_INVALID_HDL                            (0x0000)
/// Invalid attribute idx (used for profiles)
#define ESBLE_ATT_INVALID_IDX                            (0xff)

#define ESBLE_ATT_1ST_REQ_START_HDL                      0x0001
#define ESBLE_ATT_1ST_REQ_END_HDL                        0xFFFF

/// Maximum possible attribute handle
#define ESBLE_ATT_MAX_ATTR_HDL                           ESBLE_ATT_1ST_REQ_END_HDL

/// Offset of value in signed PDU
#define ESBLE_ATT_SIGNED_PDU_VAL_OFFSET               0x03

/// Attribute Features
#define ESBLE_ATT_SERVER_CONFIG                       0x0001
#define ESBLE_ATT_SERVICE_DISC                        0x0002
#define ESBLE_ATT_RELATIONSHIP_DISC                   0x0004
#define ESBLE_ATT_CHAR_DISC                           0x0008
#define ESBLE_ATT_CHAR_DESC_DISC                      0x0010
#define ESBLE_ATT_RD_CHAR_VALUE                       0x0020
#define ESBLE_ATT_WR_CHAR_VALUE                       0x0040
#define ESBLE_ATT_NOTIF_CHAR_VALUE                    0x0080
#define ESBLE_ATT_IND_CHAR_VALUE                      0x0100
#define ESBLE_ATT_RD_CHAR_DESC                        0x0200
#define ESBLE_ATT_WR_CHAR_DESC                        0x0400

/// Length, number, offset defines
#define ESBLE_ATT_SVC_VALUE_MAX_LEN                   0x0030
#define ESBLE_ATT_CHAR_NAME_MAX_LEN                   0x0030
#define ESBLE_ATT_UUID_16_LEN                         0x0002
#define ESBLE_ATT_UUID_32_LEN                         0x0004
#define ESBLE_ATT_UUID_128_LEN                        0x0010

/// offset - l2cap header and ATT code
#define ESBLE_ATT_PDU_DATA_OFFSET                     0x05

/// Characteristic Properties Bit
#define ESBLE_ATT_CHAR_PROP_BCAST                     0x01
#define ESBLE_ATT_CHAR_PROP_RD                        0x02
#define ESBLE_ATT_CHAR_PROP_WR_NO_RESP                0x04
#define ESBLE_ATT_CHAR_PROP_WR                        0x08
#define ESBLE_ATT_CHAR_PROP_NTF                       0x10
#define ESBLE_ATT_CHAR_PROP_IND                       0x20
#define ESBLE_ATT_CHAR_PROP_AUTH                      0x40
#define ESBLE_ATT_CHAR_PROP_EXT_PROP                  0x80
/// Invalid Attribute Handle
#define ESBLE_ATT_INVALID_SEARCH_HANDLE               0x0000
#define ESBLE_ATT_INVALID_HANDLE                      0x0000
/// Read Information Request
#define ESBLE_ATT_UUID_FILTER_0                       0x00
#define ESBLE_ATT_UUID_FILTER_2                       0x02
#define ESBLE_ATT_UUID_FILTER_16                      0x10
/// Read Information Response
#define ESBLE_ATT_FORMAT_LEN                          0x0001
#define ESBLE_ATT_FORMAT_16BIT_UUID                   0x01
#define ESBLE_ATT_FORMAT_128BIT_UUID                  0x02
/// For No fix length PDU
#define ESBLE_ATT_HANDLE_LEN                          0x0002
#define ESBLE_ATT_EACHLEN_LEN                         0x0001
#define ESBLE_ATT_PROP_LEN                            0x0001
#define ESBLE_ATT_CODE_LEN                            0x0001
#define ESBLE_ATT_CODE_AND_DATA_LEN                   0x0002
#define ESBLE_ATT_CODE_AND_HANDLE_LEN                 0x0003
#define ESBLE_ATT_CODE_AND_HANDLE_LEN_AND_OFFSET      0x0005
#define ESBLE_ATT_SIGNATURE_LEN                       0x0C

/// extended characteristics
#define ESBLE_ATT_EXT_RELIABLE_WRITE                  0x0001
#define ESBLE_ATT_EXT_WRITABLE_AUX                    0x0002
#define ESBLE_ATT_EXT_RFU                             0xFFFC

/// PDU size for error response
#define ESBLE_ATT_ERROR_RESP_LEN                      0x05

/// Offset of value in signed PDU
#define ESBLE_ATT_SIGNED_PDU_VAL_OFFSET               0x03



#define ESBLE_ATT_BT_UUID_128 {0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, \
								0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}


/* Attribute Specification Defines */

/// Common 16-bit Universal Unique Identifier
enum {
	ESBLE_ATT_INVALID_UUID                            = ESBLE_ATT_UUID_16(0x0000),
	/*----------------- SERVICES ---------------------*/
	/// Generic Access Profile
	ESBLE_ATT_SVC_GENERIC_ACCESS                      = ESBLE_ATT_UUID_16(0x1800),
	/// Attribute Profile
	ESBLE_ATT_SVC_GENERIC_ATTRIBUTE                   = ESBLE_ATT_UUID_16(0x1801),
	/// Immediate alert Service
	ESBLE_ATT_SVC_IMMEDIATE_ALERT                     = ESBLE_ATT_UUID_16(0x1802),
	/// Link Loss Service
	ESBLE_ATT_SVC_LINK_LOSS                           = ESBLE_ATT_UUID_16(0x1803),
	/// Tx Power Service
	ESBLE_ATT_SVC_TX_POWER                            = ESBLE_ATT_UUID_16(0x1804),
	/// Current Time Service Service
	ESBLE_ATT_SVC_CURRENT_TIME                        = ESBLE_ATT_UUID_16(0x1805),
	/// Reference Time Update Service
	ESBLE_ATT_SVC_REF_TIME_UPDATE                     = ESBLE_ATT_UUID_16(0x1806),
	/// Next DST Change Service
	ESBLE_ATT_SVC_NEXT_DST_CHANGE                     = ESBLE_ATT_UUID_16(0x1807),
	/// Glucose Service
	ESBLE_ATT_SVC_GLUCOSE                             = ESBLE_ATT_UUID_16(0x1808),
	/// Health Thermometer Service
	ESBLE_ATT_SVC_HEALTH_THERMOM                      = ESBLE_ATT_UUID_16(0x1809),
	/// Device Information Service
	ESBLE_ATT_SVC_DEVICE_INFO                         = ESBLE_ATT_UUID_16(0x180A),
	/// Heart Rate Service
	ESBLE_ATT_SVC_HEART_RATE                          = ESBLE_ATT_UUID_16(0x180D),
	/// Phone Alert Status Service
	ESBLE_ATT_SVC_PHONE_ALERT_STATUS                  = ESBLE_ATT_UUID_16(0x180E),
	/// Battery Service
	ESBLE_ATT_SVC_BATTERY_SERVICE                     = ESBLE_ATT_UUID_16(0x180F),
	/// Blood Pressure Service
	ESBLE_ATT_SVC_BLOOD_PRESSURE                      = ESBLE_ATT_UUID_16(0x1810),
	/// Alert Notification Service
	ESBLE_ATT_SVC_ALERT_NTF                           = ESBLE_ATT_UUID_16(0x1811),
	/// HID Service
	ESBLE_ATT_SVC_HID                                 = ESBLE_ATT_UUID_16(0x1812),
	/// Scan Parameters Service
	ESBLE_ATT_SVC_SCAN_PARAMETERS                     = ESBLE_ATT_UUID_16(0x1813),
	/// Running Speed and Cadence Service
	ESBLE_ATT_SVC_RUNNING_SPEED_CADENCE               = ESBLE_ATT_UUID_16(0x1814),
	/// Cycling Speed and Cadence Service
	ESBLE_ATT_SVC_CYCLING_SPEED_CADENCE               = ESBLE_ATT_UUID_16(0x1816),
	/// Cycling Power Service
	ESBLE_ATT_SVC_CYCLING_POWER                       = ESBLE_ATT_UUID_16(0x1818),
	/// Location and Navigation Service
	ESBLE_ATT_SVC_LOCATION_AND_NAVIGATION             = ESBLE_ATT_UUID_16(0x1819),
	/// Environmental Sensing Service
	ESBLE_ATT_SVC_ENVIRONMENTAL_SENSING               = ESBLE_ATT_UUID_16(0x181A),
	/// Body Composition Service
	ESBLE_ATT_SVC_BODY_COMPOSITION                    = ESBLE_ATT_UUID_16(0x181B),
	/// User Data Service
	ESBLE_ATT_SVC_USER_DATA                           = ESBLE_ATT_UUID_16(0x181C),
	/// Weight Scale Service
	ESBLE_ATT_SVC_WEIGHT_SCALE                        = ESBLE_ATT_UUID_16(0x181D),
	/// Bond Management Service
	ESBLE_ATT_SVC_BOND_MANAGEMENT                     = ESBLE_ATT_UUID_16(0x181E),
	/// Continuous Glucose Monitoring Service
	ESBLE_ATT_SVC_CONTINUOUS_GLUCOSE_MONITORING       = ESBLE_ATT_UUID_16(0x181F),
	/// Internet Protocol Support Service
	ESBLE_ATT_SVC_IP_SUPPORT                          = ESBLE_ATT_UUID_16(0x1820),
	/// Indoor Positioning Service
	ESBLE_ATT_SVC_INDOOR_POSITIONING                  = ESBLE_ATT_UUID_16(0x1821),
	/// Pulse Oximeter Service
	ESBLE_ATT_SVC_PULSE_OXIMETER                      = ESBLE_ATT_UUID_16(0x1822),
	/// HTTP Proxy Service
	ESBLE_ATT_SVC_HTTP_PROXY                          = ESBLE_ATT_UUID_16(0x1823),
	/// Transport Discovery Service
	ESBLE_ATT_SVC_TRANSPORT_DISCOVERY                 = ESBLE_ATT_UUID_16(0x1824),
	/// Object Transfer Service
	ESBLE_ATT_SVC_OBJECT_TRANSFER                     = ESBLE_ATT_UUID_16(0x1825),
	/// Mesh Provisioning Service
	ESBLE_ATT_SVC_MESH_PROVISIONING                   = ESBLE_ATT_UUID_16(0x1827),
	/// Mesh Proxy Service
	ESBLE_ATT_SVC_MESH_PROXY                          = ESBLE_ATT_UUID_16(0x1828),

	/*------------------- UNITS ---------------------*/
	/// No defined unit
	ESBLE_ATT_UNIT_UNITLESS                           = ESBLE_ATT_UUID_16(0x2700),
	/// Length Unit - Metre
	ESBLE_ATT_UNIT_METRE                              = ESBLE_ATT_UUID_16(0x2701),
	///Mass unit - Kilogram
	ESBLE_ATT_UNIT_KG                                 = ESBLE_ATT_UUID_16(0x2702),
	///Time unit - second
	ESBLE_ATT_UNIT_SECOND                             = ESBLE_ATT_UUID_16(0x2703),
	///Electric current unit - Ampere
	ESBLE_ATT_UNIT_AMPERE                             = ESBLE_ATT_UUID_16(0x2704),
	///Thermodynamic Temperature unit - Kelvin
	ESBLE_ATT_UNIT_KELVIN                             = ESBLE_ATT_UUID_16(0x2705),
	/// Amount of substance unit - mole
	ESBLE_ATT_UNIT_MOLE                               = ESBLE_ATT_UUID_16(0x2706),
	///Luminous intensity unit - candela
	ESBLE_ATT_UNIT_CANDELA                            = ESBLE_ATT_UUID_16(0x2707),
	///Area unit - square metres
	ESBLE_ATT_UNIT_SQ_METRE                           = ESBLE_ATT_UUID_16(0x2710),
	///Colume unit - cubic metres
	ESBLE_ATT_UNIT_CUBIC_METRE                        = ESBLE_ATT_UUID_16(0x2710),
	///Velocity unit - metres per second
	ESBLE_ATT_UNIT_METRE_PER_SECOND                   = ESBLE_ATT_UUID_16(0x2711),
	///Acceleration unit - metres per second squared
	ESBLE_ATT_UNIT_METRES_PER_SEC_SQ                  = ESBLE_ATT_UUID_16(0x2712),
	///Wavenumber unit - reciprocal metre
	ESBLE_ATT_UNIT_RECIPROCAL_METRE                   = ESBLE_ATT_UUID_16(0x2713),
	///Density unit - kilogram per cubic metre
	ESBLE_ATT_UNIT_DENS_KG_PER_CUBIC_METRE            = ESBLE_ATT_UUID_16(0x2714),
	///Surface density unit - kilogram per square metre
	ESBLE_ATT_UNIT_KG_PER_SQ_METRE                    = ESBLE_ATT_UUID_16(0x2715),
	///Specific volume unit - cubic metre per kilogram
	ESBLE_ATT_UNIT_CUBIC_METRE_PER_KG                 = ESBLE_ATT_UUID_16(0x2716),
	///Current density unit - ampere per square metre
	ESBLE_ATT_UNIT_AMPERE_PER_SQ_METRE                = ESBLE_ATT_UUID_16(0x2717),
	///Magnetic field strength unit - Ampere per metre
	ESBLE_ATT_UNIT_AMPERE_PER_METRE                   = ESBLE_ATT_UUID_16(0x2718),
	///Amount concentration unit - mole per cubic metre
	ESBLE_ATT_UNIT_MOLE_PER_CUBIC_METRE               = ESBLE_ATT_UUID_16(0x2719),
	///Mass Concentration unit - kilogram per cubic metre
	ESBLE_ATT_UNIT_MASS_KG_PER_CUBIC_METRE            = ESBLE_ATT_UUID_16(0x271A),
	///Luminance unit - candela per square metre
	ESBLE_ATT_UNIT_CANDELA_PER_SQ_METRE               = ESBLE_ATT_UUID_16(0x271B),
	///Refractive index unit
	ESBLE_ATT_UNIT_REFRACTIVE_INDEX                   = ESBLE_ATT_UUID_16(0x271C),
	///Relative permeability unit
	ESBLE_ATT_UNIT_RELATIVE_PERMEABILITY              = ESBLE_ATT_UUID_16(0x271D),
	///Plane angle unit - radian
	ESBLE_ATT_UNIT_RADIAN                             = ESBLE_ATT_UUID_16(0x2720),
	///Solid angle unit - steradian
	ESBLE_ATT_UNIT_STERADIAN                          = ESBLE_ATT_UUID_16(0x2721),
	///Frequency unit - Hertz
	ESBLE_ATT_UNIT_HERTZ                              = ESBLE_ATT_UUID_16(0x2722),
	///Force unit - Newton
	ESBLE_ATT_UNIT_NEWTON                             = ESBLE_ATT_UUID_16(0x2723),
	///Pressure unit - Pascal
	ESBLE_ATT_UNIT_PASCAL                             = ESBLE_ATT_UUID_16(0x2724),
	///Energy unit - Joule
	ESBLE_ATT_UNIT_JOULE                              = ESBLE_ATT_UUID_16(0x2725),
	///Power unit - Watt
	ESBLE_ATT_UNIT_WATT                               = ESBLE_ATT_UUID_16(0x2726),
	///electric Charge unit - Coulomb
	ESBLE_ATT_UNIT_COULOMB                            = ESBLE_ATT_UUID_16(0x2727),
	///Electric potential difference - Volt
	ESBLE_ATT_UNIT_VOLT                               = ESBLE_ATT_UUID_16(0x2728),
	///Capacitance unit - Farad
	ESBLE_ATT_UNIT_FARAD                              = ESBLE_ATT_UUID_16(0x2729),
	///electric resistance unit - Ohm
	ESBLE_ATT_UNIT_OHM                                = ESBLE_ATT_UUID_16(0x272A),
	///Electric conductance - Siemens
	ESBLE_ATT_UNIT_SIEMENS                            = ESBLE_ATT_UUID_16(0x272B),
	///Magnetic flux unit - Weber
	ESBLE_ATT_UNIT_WEBER                              = ESBLE_ATT_UUID_16(0x272C),
	///Magnetic flux density unit - Tesla
	ESBLE_ATT_UNIT_TESLA                              = ESBLE_ATT_UUID_16(0x272D),
	///Inductance unit - Henry
	ESBLE_ATT_UNIT_HENRY                              = ESBLE_ATT_UUID_16(0x272E),
	///Temperature unit - degree Celsius
	ESBLE_ATT_UNIT_CELSIUS                            = ESBLE_ATT_UUID_16(0x272F),
	///Luminous flux unit - lumen
	ESBLE_ATT_UNIT_LUMEN                              = ESBLE_ATT_UUID_16(0x2730),
	///Illuminance unit - lux
	ESBLE_ATT_UNIT_LUX                                = ESBLE_ATT_UUID_16(0x2731),
	///Activity referred to a radionuclide unit - becquerel
	ESBLE_ATT_UNIT_BECQUEREL                          = ESBLE_ATT_UUID_16(0x2732),
	///Absorbed dose unit - Gray
	ESBLE_ATT_UNIT_GRAY                               = ESBLE_ATT_UUID_16(0x2733),
	///Dose equivalent unit - Sievert
	ESBLE_ATT_UNIT_SIEVERT                            = ESBLE_ATT_UUID_16(0x2734),
	///Catalytic activity unit - Katal
	ESBLE_ATT_UNIT_KATAL                              = ESBLE_ATT_UUID_16(0x2735),
	///Synamic viscosity unit - Pascal second
	ESBLE_ATT_UNIT_PASCAL_SECOND                      = ESBLE_ATT_UUID_16(0x2740),
	///Moment of force unit - Newton metre
	ESBLE_ATT_UNIT_NEWTON_METRE                       = ESBLE_ATT_UUID_16(0x2741),
	///surface tension unit - Newton per metre
	ESBLE_ATT_UNIT_NEWTON_PER_METRE                   = ESBLE_ATT_UUID_16(0x2742),
	///Angular velocity unit - radian per second
	ESBLE_ATT_UNIT_RADIAN_PER_SECOND                  = ESBLE_ATT_UUID_16(0x2743),
	///Angular acceleration unit - radian per second squared
	ESBLE_ATT_UNIT_RADIAN_PER_SECOND_SQ               = ESBLE_ATT_UUID_16(0x2744),
	///Heat flux density unit - Watt per square metre
	ESBLE_ATT_UNIT_WATT_PER_SQ_METRE                  = ESBLE_ATT_UUID_16(0x2745),
	///HEat capacity unit - Joule per Kelvin
	ESBLE_ATT_UNIT_JOULE_PER_KELVIN                   = ESBLE_ATT_UUID_16(0x2746),
	///Specific heat capacity unit - Joule per kilogram kelvin
	ESBLE_ATT_UNIT_JOULE_PER_KG_KELVIN                = ESBLE_ATT_UUID_16(0x2747),
	///Specific Energy unit - Joule per kilogram
	ESBLE_ATT_UNIT_JOULE_PER_KG                       = ESBLE_ATT_UUID_16(0x2748),
	///Thermal conductivity - Watt per metre Kelvin
	ESBLE_ATT_UNIT_WATT_PER_METRE_KELVIN              = ESBLE_ATT_UUID_16(0x2749),
	///Energy Density unit - joule per cubic metre
	ESBLE_ATT_UNIT_JOULE_PER_CUBIC_METRE              = ESBLE_ATT_UUID_16(0x274A),
	///Electric field strength unit - volt per metre
	ESBLE_ATT_UNIT_VOLT_PER_METRE                     = ESBLE_ATT_UUID_16(0x274B),
	///Electric charge density unit - coulomb per cubic metre
	ESBLE_ATT_UNIT_COULOMB_PER_CUBIC_METRE            = ESBLE_ATT_UUID_16(0x274C),
	///Surface charge density unit - coulomb per square metre
	ESBLE_ATT_UNIT_SURF_COULOMB_PER_SQ_METRE          = ESBLE_ATT_UUID_16(0x274D),
	///Electric flux density unit - coulomb per square metre
	ESBLE_ATT_UNIT_FLUX_COULOMB_PER_SQ_METRE          = ESBLE_ATT_UUID_16(0x274E),
	///Permittivity unit - farad per metre
	ESBLE_ATT_UNIT_FARAD_PER_METRE                    = ESBLE_ATT_UUID_16(0x274F),
	///Permeability unit - henry per metre
	ESBLE_ATT_UNIT_HENRY_PER_METRE                    = ESBLE_ATT_UUID_16(0x2750),
	///Molar energy unit - joule per mole
	ESBLE_ATT_UNIT_JOULE_PER_MOLE                     = ESBLE_ATT_UUID_16(0x2751),
	///Molar entropy unit - joule per mole kelvin
	ESBLE_ATT_UNIT_JOULE_PER_MOLE_KELVIN              = ESBLE_ATT_UUID_16(0x2752),
	///Exposure unit - coulomb per kilogram
	ESBLE_ATT_UNIT_COULOMB_PER_KG                     = ESBLE_ATT_UUID_16(0x2753),
	///Absorbed dose rate unit - gray per second
	ESBLE_ATT_UNIT_GRAY_PER_SECOND                    = ESBLE_ATT_UUID_16(0x2754),
	///Radiant intensity unit - watt per steradian
	ESBLE_ATT_UNIT_WATT_PER_STERADIAN                 = ESBLE_ATT_UUID_16(0x2755),
	///Radiance unit - watt per square meter steradian
	ESBLE_ATT_UNIT_WATT_PER_SQ_METRE_STERADIAN        = ESBLE_ATT_UUID_16(0x2756),
	///Catalytic activity concentration unit - katal per cubic metre
	ESBLE_ATT_UNIT_KATAL_PER_CUBIC_METRE              = ESBLE_ATT_UUID_16(0x2757),
	///Time unit - minute
	ESBLE_ATT_UNIT_MINUTE                             = ESBLE_ATT_UUID_16(0x2760),
	///Time unit - hour
	ESBLE_ATT_UNIT_HOUR                               = ESBLE_ATT_UUID_16(0x2761),
	///Time unit - day
	ESBLE_ATT_UNIT_DAY                                = ESBLE_ATT_UUID_16(0x2762),
	///Plane angle unit - degree
	ESBLE_ATT_UNIT_ANGLE_DEGREE                       = ESBLE_ATT_UUID_16(0x2763),
	///Plane angle unit - minute
	ESBLE_ATT_UNIT_ANGLE_MINUTE                       = ESBLE_ATT_UUID_16(0x2764),
	///Plane angle unit - second
	ESBLE_ATT_UNIT_ANGLE_SECOND                       = ESBLE_ATT_UUID_16(0x2765),
	///Area unit - hectare
	ESBLE_ATT_UNIT_HECTARE                            = ESBLE_ATT_UUID_16(0x2766),
	///Volume unit - litre
	ESBLE_ATT_UNIT_LITRE                              = ESBLE_ATT_UUID_16(0x2767),
	///Mass unit - tonne
	ESBLE_ATT_UNIT_TONNE                              = ESBLE_ATT_UUID_16(0x2768),
	///Pressure unit - bar
	ESBLE_ATT_UNIT_BAR                                = ESBLE_ATT_UUID_16(0x2780),
	///Pressure unit - millimetre of mercury
	ESBLE_ATT_UNIT_MM_MERCURY                         = ESBLE_ATT_UUID_16(0x2781),
	///Length unit - angstrom
	ESBLE_ATT_UNIT_ANGSTROM                           = ESBLE_ATT_UUID_16(0x2782),
	///Length unit - nautical mile
	ESBLE_ATT_UNIT_NAUTICAL_MILE                      = ESBLE_ATT_UUID_16(0x2783),
	///Area unit - barn
	ESBLE_ATT_UNIT_BARN                               = ESBLE_ATT_UUID_16(0x2784),
	///Velocity unit - knot
	ESBLE_ATT_UNIT_KNOT                               = ESBLE_ATT_UUID_16(0x2785),
	///Logarithmic radio quantity unit - neper
	ESBLE_ATT_UNIT_NEPER                              = ESBLE_ATT_UUID_16(0x2786),
	///Logarithmic radio quantity unit - bel
	ESBLE_ATT_UNIT_BEL                                = ESBLE_ATT_UUID_16(0x2787),
	///Length unit - yard
	ESBLE_ATT_UNIT_YARD                               = ESBLE_ATT_UUID_16(0x27A0),
	///Length unit - parsec
	ESBLE_ATT_UNIT_PARSEC                             = ESBLE_ATT_UUID_16(0x27A1),
	///length unit - inch
	ESBLE_ATT_UNIT_INCH                               = ESBLE_ATT_UUID_16(0x27A2),
	///length unit - foot
	ESBLE_ATT_UNIT_FOOT                               = ESBLE_ATT_UUID_16(0x27A3),
	///length unit - mile
	ESBLE_ATT_UNIT_MILE                               = ESBLE_ATT_UUID_16(0x27A4),
	///pressure unit - pound-force per square inch
	ESBLE_ATT_UNIT_POUND_FORCE_PER_SQ_INCH            = ESBLE_ATT_UUID_16(0x27A5),
	///velocity unit - kilometre per hour
	ESBLE_ATT_UNIT_KM_PER_HOUR                        = ESBLE_ATT_UUID_16(0x27A6),
	///velocity unit - mile per hour
	ESBLE_ATT_UNIT_MILE_PER_HOUR                      = ESBLE_ATT_UUID_16(0x27A7),
	///angular velocity unit - revolution per minute
	ESBLE_ATT_UNIT_REVOLUTION_PER_MINUTE              = ESBLE_ATT_UUID_16(0x27A8),
	///energy unit - gram calorie
	ESBLE_ATT_UNIT_GRAM_CALORIE                       = ESBLE_ATT_UUID_16(0x27A9),
	///energy unit - kilogram calorie
	ESBLE_ATT_UNIT_KG_CALORIE                         = ESBLE_ATT_UUID_16(0x27AA),
	/// energy unit - kilowatt hour
	ESBLE_ATT_UNIT_KILOWATT_HOUR                      = ESBLE_ATT_UUID_16(0x27AB),
	///thermodynamic temperature unit - degree Fahrenheit
	ESBLE_ATT_UNIT_FAHRENHEIT                         = ESBLE_ATT_UUID_16(0x27AC),
	///percentage
	ESBLE_ATT_UNIT_PERCENTAGE                         = ESBLE_ATT_UUID_16(0x27AD),
	///per mille
	ESBLE_ATT_UNIT_PER_MILLE                          = ESBLE_ATT_UUID_16(0x27AE),
	///period unit - beats per minute)
	ESBLE_ATT_UNIT_BEATS_PER_MINUTE                   = ESBLE_ATT_UUID_16(0x27AF),
	///electric charge unit - ampere hours
	ESBLE_ATT_UNIT_AMPERE_HOURS                       = ESBLE_ATT_UUID_16(0x27B0),
	///mass density unit - milligram per decilitre
	ESBLE_ATT_UNIT_MILLIGRAM_PER_DECILITRE            = ESBLE_ATT_UUID_16(0x27B1),
	///mass density unit - millimole per litre
	ESBLE_ATT_UNIT_MILLIMOLE_PER_LITRE                = ESBLE_ATT_UUID_16(0x27B2),
	///time unit - year
	ESBLE_ATT_UNIT_YEAR                               = ESBLE_ATT_UUID_16(0x27B3),
	////time unit - month
	ESBLE_ATT_UNIT_MONTH                              = ESBLE_ATT_UUID_16(0x27B4),


	/*---------------- DECLARATIONS -----------------*/
	/// Primary service Declaration
	ESBLE_ATT_DECL_PRIMARY_SERVICE                     = ESBLE_ATT_UUID_16(0x2800),
	/// Secondary service Declaration
	ESBLE_ATT_DECL_SECONDARY_SERVICE                   = ESBLE_ATT_UUID_16(0x2801),
	/// Include Declaration
	ESBLE_ATT_DECL_INCLUDE                             = ESBLE_ATT_UUID_16(0x2802),
	/// Characteristic Declaration
	ESBLE_ATT_DECL_CHARACTERISTIC                      = ESBLE_ATT_UUID_16(0x2803),


	/*----------------- DESCRIPTORS -----------------*/
	/// Characteristic extended properties
	ESBLE_ATT_DESC_CHAR_EXT_PROPERTIES                 = ESBLE_ATT_UUID_16(0x2900),
	/// Characteristic user description
	ESBLE_ATT_DESC_CHAR_USER_DESCRIPTION               = ESBLE_ATT_UUID_16(0x2901),
	/// Client characteristic configuration
	ESBLE_ATT_DESC_CLIENT_CHAR_CFG                     = ESBLE_ATT_UUID_16(0x2902),
	/// Server characteristic configuration
	ESBLE_ATT_DESC_SERVER_CHAR_CFG                     = ESBLE_ATT_UUID_16(0x2903),
	/// Characteristic Presentation Format
	ESBLE_ATT_DESC_CHAR_PRES_FORMAT                    = ESBLE_ATT_UUID_16(0x2904),
	/// Characteristic Aggregate Format
	ESBLE_ATT_DESC_CHAR_AGGREGATE_FORMAT               = ESBLE_ATT_UUID_16(0x2905),
	/// Valid Range
	ESBLE_ATT_DESC_VALID_RANGE                         = ESBLE_ATT_UUID_16(0x2906),
	/// External Report Reference
	ESBLE_ATT_DESC_EXT_REPORT_REF                      = ESBLE_ATT_UUID_16(0x2907),
	/// Report Reference
	ESBLE_ATT_DESC_REPORT_REF                          = ESBLE_ATT_UUID_16(0x2908),
	/// Environmental Sensing Configuration
	ESBLE_ATT_DESC_ES_CONFIGURATION                    = ESBLE_ATT_UUID_16(0x290B),
	/// Environmental Sensing Measurement
	ESBLE_ATT_DESC_ES_MEASUREMENT                      = ESBLE_ATT_UUID_16(0x290C),
	/// Environmental Sensing Trigger Setting
	ESBLE_ATT_DESC_ES_TRIGGER_SETTING                  = ESBLE_ATT_UUID_16(0x290D),


	/*--------------- CHARACTERISTICS ---------------*/
	/// Device name
	ESBLE_ATT_CHAR_DEVICE_NAME                        = ESBLE_ATT_UUID_16(0x2A00),
	/// Appearance
	ESBLE_ATT_CHAR_APPEARANCE                         = ESBLE_ATT_UUID_16(0x2A01),
	/// Privacy flag
	ESBLE_ATT_CHAR_PRIVACY_FLAG                       = ESBLE_ATT_UUID_16(0x2A02),
	/// Reconnection address
	ESBLE_ATT_CHAR_RECONNECTION_ADDR                  = ESBLE_ATT_UUID_16(0x2A03),
	/// Peripheral preferred connection parameters
	ESBLE_ATT_CHAR_PERIPH_PREF_CON_PARAM              = ESBLE_ATT_UUID_16(0x2A04),
	/// Service handles changed
	ESBLE_ATT_CHAR_SERVICE_CHANGED                    = ESBLE_ATT_UUID_16(0x2A05),
	/// Alert Level characteristic
	ESBLE_ATT_CHAR_ALERT_LEVEL                        = ESBLE_ATT_UUID_16(0x2A06),
	/// Tx Power Level
	ESBLE_ATT_CHAR_TX_POWER_LEVEL                     = ESBLE_ATT_UUID_16(0x2A07),
	/// Date Time
	ESBLE_ATT_CHAR_DATE_TIME                          = ESBLE_ATT_UUID_16(0x2A08),
	/// Day of Week
	ESBLE_ATT_CHAR_DAY_WEEK                           = ESBLE_ATT_UUID_16(0x2A09),
	/// Day Date Time
	ESBLE_ATT_CHAR_DAY_DATE_TIME                      = ESBLE_ATT_UUID_16(0x2A0A),
	/// Exact time 256
	ESBLE_ATT_CHAR_EXACT_TIME_256                     = ESBLE_ATT_UUID_16(0x2A0C),
	/// DST Offset
	ESBLE_ATT_CHAR_DST_OFFSET                         = ESBLE_ATT_UUID_16(0x2A0D),
	/// Time zone
	ESBLE_ATT_CHAR_TIME_ZONE                          = ESBLE_ATT_UUID_16(0x2A0E),
	/// Local time Information
	ESBLE_ATT_CHAR_LOCAL_TIME_INFO                    = ESBLE_ATT_UUID_16(0x2A0F),
	/// Time with DST
	ESBLE_ATT_CHAR_TIME_WITH_DST                      = ESBLE_ATT_UUID_16(0x2A11),
	/// Time Accuracy
	ESBLE_ATT_CHAR_TIME_ACCURACY                      = ESBLE_ATT_UUID_16(0x2A12),
	///Time Source
	ESBLE_ATT_CHAR_TIME_SOURCE                        = ESBLE_ATT_UUID_16(0x2A13),
	/// Reference Time Information
	ESBLE_ATT_CHAR_REFERENCE_TIME_INFO                = ESBLE_ATT_UUID_16(0x2A14),
	/// Time Update Control Point
	ESBLE_ATT_CHAR_TIME_UPDATE_CNTL_POINT             = ESBLE_ATT_UUID_16(0x2A16),
	/// Time Update State
	ESBLE_ATT_CHAR_TIME_UPDATE_STATE                  = ESBLE_ATT_UUID_16(0x2A17),
	/// Glucose Measurement
	ESBLE_ATT_CHAR_GLUCOSE_MEAS                       = ESBLE_ATT_UUID_16(0x2A18),
	/// Battery Level
	ESBLE_ATT_CHAR_BATTERY_LEVEL                      = ESBLE_ATT_UUID_16(0x2A19),
	/// Temperature Measurement
	ESBLE_ATT_CHAR_TEMPERATURE_MEAS                   = ESBLE_ATT_UUID_16(0x2A1C),
	/// Temperature Type
	ESBLE_ATT_CHAR_TEMPERATURE_TYPE                   = ESBLE_ATT_UUID_16(0x2A1D),
	/// Intermediate Temperature
	ESBLE_ATT_CHAR_INTERMED_TEMPERATURE               = ESBLE_ATT_UUID_16(0x2A1E),
	/// Measurement Interval
	ESBLE_ATT_CHAR_MEAS_INTERVAL                      = ESBLE_ATT_UUID_16(0x2A21),
	/// Boot Keyboard Input Report
	ESBLE_ATT_CHAR_BOOT_KB_IN_REPORT                  = ESBLE_ATT_UUID_16(0x2A22),
	/// System ID
	ESBLE_ATT_CHAR_SYS_ID                             = ESBLE_ATT_UUID_16(0x2A23),
	/// Model Number String
	ESBLE_ATT_CHAR_MODEL_NB                           = ESBLE_ATT_UUID_16(0x2A24),
	/// Serial Number String
	ESBLE_ATT_CHAR_SERIAL_NB                          = ESBLE_ATT_UUID_16(0x2A25),
	/// Firmware Revision String
	ESBLE_ATT_CHAR_FW_REV                             = ESBLE_ATT_UUID_16(0x2A26),
	/// Hardware revision String
	ESBLE_ATT_CHAR_HW_REV                             = ESBLE_ATT_UUID_16(0x2A27),
	/// Software Revision String
	ESBLE_ATT_CHAR_SW_REV                             = ESBLE_ATT_UUID_16(0x2A28),
	/// Manufacturer Name String
	ESBLE_ATT_CHAR_MANUF_NAME                         = ESBLE_ATT_UUID_16(0x2A29),
	/// IEEE Regulatory Certification Data List
	ESBLE_ATT_CHAR_IEEE_CERTIF                        = ESBLE_ATT_UUID_16(0x2A2A),
	/// CT Time
	ESBLE_ATT_CHAR_CT_TIME                            = ESBLE_ATT_UUID_16(0x2A2B),
	/// Magnetic Declination
	ESBLE_ATT_CHAR_MAGN_DECLINE                       = ESBLE_ATT_UUID_16(0x2A2C),
	/// Scan Refresh
	ESBLE_ATT_CHAR_SCAN_REFRESH                       = ESBLE_ATT_UUID_16(0x2A31),
	/// Boot Keyboard Output Report
	ESBLE_ATT_CHAR_BOOT_KB_OUT_REPORT                 = ESBLE_ATT_UUID_16(0x2A32),
	/// Boot Mouse Input Report
	ESBLE_ATT_CHAR_BOOT_MOUSE_IN_REPORT               = ESBLE_ATT_UUID_16(0x2A33),
	/// Glucose Measurement Context
	ESBLE_ATT_CHAR_GLUCOSE_MEAS_CTX                   = ESBLE_ATT_UUID_16(0x2A34),
	/// Blood Pressure Measurement
	ESBLE_ATT_CHAR_BLOOD_PRESSURE_MEAS                = ESBLE_ATT_UUID_16(0x2A35),
	/// Intermediate Cuff Pressure
	ESBLE_ATT_CHAR_INTERMEDIATE_CUFF_PRESSURE         = ESBLE_ATT_UUID_16(0x2A36),
	/// Heart Rate Measurement
	ESBLE_ATT_CHAR_HEART_RATE_MEAS                    = ESBLE_ATT_UUID_16(0x2A37),
	/// Body Sensor Location
	ESBLE_ATT_CHAR_BODY_SENSOR_LOCATION               = ESBLE_ATT_UUID_16(0x2A38),
	/// Heart Rate Control Point
	ESBLE_ATT_CHAR_HEART_RATE_CNTL_POINT              = ESBLE_ATT_UUID_16(0x2A39),
	/// Alert Status
	ESBLE_ATT_CHAR_ALERT_STATUS                       = ESBLE_ATT_UUID_16(0x2A3F),
	/// Ringer Control Point
	ESBLE_ATT_CHAR_RINGER_CNTL_POINT                  = ESBLE_ATT_UUID_16(0x2A40),
	/// Ringer Setting
	ESBLE_ATT_CHAR_RINGER_SETTING                     = ESBLE_ATT_UUID_16(0x2A41),
	/// Alert Category ID Bit Mask
	ESBLE_ATT_CHAR_ALERT_CAT_ID_BIT_MASK              = ESBLE_ATT_UUID_16(0x2A42),
	/// Alert Category ID
	ESBLE_ATT_CHAR_ALERT_CAT_ID                       = ESBLE_ATT_UUID_16(0x2A43),
	/// Alert Notification Control Point
	ESBLE_ATT_CHAR_ALERT_NTF_CTNL_PT                  = ESBLE_ATT_UUID_16(0x2A44),
	/// Unread Alert Status
	ESBLE_ATT_CHAR_UNREAD_ALERT_STATUS                = ESBLE_ATT_UUID_16(0x2A45),
	/// New Alert
	ESBLE_ATT_CHAR_NEW_ALERT                          = ESBLE_ATT_UUID_16(0x2A46),
	/// Supported New Alert Category
	ESBLE_ATT_CHAR_SUP_NEW_ALERT_CAT                  = ESBLE_ATT_UUID_16(0x2A47),
	/// Supported Unread Alert Category
	ESBLE_ATT_CHAR_SUP_UNREAD_ALERT_CAT               = ESBLE_ATT_UUID_16(0x2A48),
	/// Blood Pressure Feature
	ESBLE_ATT_CHAR_BLOOD_PRESSURE_FEATURE             = ESBLE_ATT_UUID_16(0x2A49),
	/// HID Information
	ESBLE_ATT_CHAR_HID_INFO                           = ESBLE_ATT_UUID_16(0x2A4A),
	/// Report Map
	ESBLE_ATT_CHAR_REPORT_MAP                         = ESBLE_ATT_UUID_16(0x2A4B),
	/// HID Control Point
	ESBLE_ATT_CHAR_HID_CTNL_PT                        = ESBLE_ATT_UUID_16(0x2A4C),
	/// Report
	ESBLE_ATT_CHAR_REPORT                             = ESBLE_ATT_UUID_16(0x2A4D),
	/// Protocol Mode
	ESBLE_ATT_CHAR_PROTOCOL_MODE                      = ESBLE_ATT_UUID_16(0x2A4E),
	/// Scan Interval Window
	ESBLE_ATT_CHAR_SCAN_INTV_WD                       = ESBLE_ATT_UUID_16(0x2A4F),
	/// PnP ID
	ESBLE_ATT_CHAR_PNP_ID                             = ESBLE_ATT_UUID_16(0x2A50),
	/// Glucose Feature
	ESBLE_ATT_CHAR_GLUCOSE_FEATURE                    = ESBLE_ATT_UUID_16(0x2A51),
	/// Record access control point
	ESBLE_ATT_CHAR_REC_ACCESS_CTRL_PT                 = ESBLE_ATT_UUID_16(0x2A52),
	/// RSC Measurement
	ESBLE_ATT_CHAR_RSC_MEAS                           = ESBLE_ATT_UUID_16(0x2A53),
	/// RSC Feature
	ESBLE_ATT_CHAR_RSC_FEAT                           = ESBLE_ATT_UUID_16(0x2A54),
	/// SC Control Point
	ESBLE_ATT_CHAR_SC_CNTL_PT                         = ESBLE_ATT_UUID_16(0x2A55),
	/// CSC Measurement
	ESBLE_ATT_CHAR_CSC_MEAS                           = ESBLE_ATT_UUID_16(0x2A5B),
	/// CSC Feature
	ESBLE_ATT_CHAR_CSC_FEAT                           = ESBLE_ATT_UUID_16(0x2A5C),
	/// Sensor Location
	ESBLE_ATT_CHAR_SENSOR_LOC                         = ESBLE_ATT_UUID_16(0x2A5D),
	/// PLX Spot-Check Measurement
	ESBLE_ATT_CHAR_PLX_SPOT_CHECK_MEASUREMENT_LOC     = ESBLE_ATT_UUID_16(0x2A5E),
	/// PLX Continuous Measurement
	ESBLE_ATT_CHAR_PLX_CONTINUOUS_MEASUREMENT_LOC     = ESBLE_ATT_UUID_16(0x2A5F),
	/// PLX Features
	ESBLE_ATT_CHAR_PLX_FEATURES_LOC                   = ESBLE_ATT_UUID_16(0x2A60),
	/// CP Measurement
	ESBLE_ATT_CHAR_CP_MEAS                            = ESBLE_ATT_UUID_16(0x2A63),
	/// CP Vector
	ESBLE_ATT_CHAR_CP_VECTOR                          = ESBLE_ATT_UUID_16(0x2A64),
	/// CP Feature
	ESBLE_ATT_CHAR_CP_FEAT                            = ESBLE_ATT_UUID_16(0x2A65),
	/// CP Control Point
	ESBLE_ATT_CHAR_CP_CNTL_PT                         = ESBLE_ATT_UUID_16(0x2A66),
	/// Location and Speed
	ESBLE_ATT_CHAR_LOC_SPEED                          = ESBLE_ATT_UUID_16(0x2A67),
	/// Navigation
	ESBLE_ATT_CHAR_NAVIGATION                         = ESBLE_ATT_UUID_16(0x2A68),
	/// Position Quality
	ESBLE_ATT_CHAR_POS_QUALITY                        = ESBLE_ATT_UUID_16(0x2A69),
	/// LN Feature
	ESBLE_ATT_CHAR_LN_FEAT                            = ESBLE_ATT_UUID_16(0x2A6A),
	/// LN Control Point
	ESBLE_ATT_CHAR_LN_CNTL_PT                         = ESBLE_ATT_UUID_16(0x2A6B),
	/// Elevation
	ESBLE_ATT_CHAR_ELEVATION                          = ESBLE_ATT_UUID_16(0x2A6C),
	/// Pressure
	ESBLE_ATT_CHAR_PRESSURE                           = ESBLE_ATT_UUID_16(0x2A6D),
	/// Temperature
	ESBLE_ATT_CHAR_TEMPERATURE                        = ESBLE_ATT_UUID_16(0x2A6E),
	/// Humidity
	ESBLE_ATT_CHAR_HUMIDITY                           = ESBLE_ATT_UUID_16(0x2A6F),
	/// True Wind Speed
	ESBLE_ATT_CHAR_TRUE_WIND_SPEED                    = ESBLE_ATT_UUID_16(0x2A70),
	/// True Wind Direction
	ESBLE_ATT_CHAR_TRUE_WIND_DIR                      = ESBLE_ATT_UUID_16(0x2A71),
	/// Apparent Wind Speed
	ESBLE_ATT_CHAR_APRNT_WIND_SPEED                   = ESBLE_ATT_UUID_16(0x2A72),
	/// Apparent Wind Direction
	ESBLE_ATT_CHAR_APRNT_WIND_DIRECTION               = ESBLE_ATT_UUID_16(0x2A73),
	/// Gust Factor
	ESBLE_ATT_CHAR_GUST_FACTOR                        = ESBLE_ATT_UUID_16(0x2A74),
	/// Pollen Concentration
	ESBLE_ATT_CHAR_POLLEN_CONC                        = ESBLE_ATT_UUID_16(0x2A75),
	/// UV Index
	ESBLE_ATT_CHAR_UV_INDEX                           = ESBLE_ATT_UUID_16(0x2A76),
	/// Irradiance
	ESBLE_ATT_CHAR_IRRADIANCE                         = ESBLE_ATT_UUID_16(0x2A77),
	/// Rainfall
	ESBLE_ATT_CHAR_RAINFALL                           = ESBLE_ATT_UUID_16(0x2A78),
	/// Wind Chill
	ESBLE_ATT_CHAR_WIND_CHILL                         = ESBLE_ATT_UUID_16(0x2A79),
	/// Heat Index
	ESBLE_ATT_CHAR_HEAT_INDEX                         = ESBLE_ATT_UUID_16(0x2A7A),
	/// Dew Point
	ESBLE_ATT_CHAR_DEW_POINT                          = ESBLE_ATT_UUID_16(0x2A7B),
	/// Descriptor Value Changed
	ESBLE_ATT_CHAR_DESCRIPTOR_VALUE_CHANGED           = ESBLE_ATT_UUID_16(0x2A7D),
	/// Aerobic Heart Rate Lower Limit
	ESBLE_ATT_CHAR_AEROBIC_HEART_RATE_LOWER_LIMIT     = ESBLE_ATT_UUID_16(0x2A7E),
	/// Aerobic Threshhold
	ESBLE_ATT_CHAR_AEROBIC_THRESHHOLD                 = ESBLE_ATT_UUID_16(0x2A7F),
	/// Age
	ESBLE_ATT_CHAR_AGE                                = ESBLE_ATT_UUID_16(0x2A80),
	/// Anaerobic Heart Rate Lower Limit
	ESBLE_ATT_CHAR_ANAEROBIC_HEART_RATE_LOWER_LIMIT   = ESBLE_ATT_UUID_16(0x2A81),
	/// Anaerobic Heart Rate Upper Limit
	ESBLE_ATT_CHAR_ANAEROBIC_HEART_RATE_UPPER_LIMIT   = ESBLE_ATT_UUID_16(0x2A82),
	/// Anaerobic Threshhold
	ESBLE_ATT_CHAR_ANAEROBIC_THRESHHOLD               = ESBLE_ATT_UUID_16(0x2A83),
	/// Aerobic Heart Rate Upper Limit
	ESBLE_ATT_CHAR_AEROBIC_HEART_RATE_UPPER_LIMIT     = ESBLE_ATT_UUID_16(0x2A84),
	/// Date Of Birth
	ESBLE_ATT_CHAR_DATE_OF_BIRTH                      = ESBLE_ATT_UUID_16(0x2A85),
	/// Date Of Threshold Assessment
	ESBLE_ATT_CHAR_DATE_OF_THRESHOLD_ASSESSMENT       = ESBLE_ATT_UUID_16(0x2A86),
	/// Email Address
	ESBLE_ATT_CHAR_EMAIL_ADDRESS                      = ESBLE_ATT_UUID_16(0x2A87),
	/// Fat Burn Heart Rate Lower Limit
	ESBLE_ATT_CHAR_FAT_BURN_HEART_RATE_LOWER_LIMIT    = ESBLE_ATT_UUID_16(0x2A88),
	/// Fat Burn Heart Rate Upper Limit
	ESBLE_ATT_CHAR_FAT_BURN_HEART_RATE_UPPER_LIMIT    = ESBLE_ATT_UUID_16(0x2A89),
	/// First Name
	ESBLE_ATT_CHAR_FIRST_NAME                         = ESBLE_ATT_UUID_16(0x2A8A),
	/// Five Zone Heart Rate Limits
	ESBLE_ATT_CHAR_FIVE_ZONE_HEART_RATE_LIMITS        = ESBLE_ATT_UUID_16(0x2A8B),
	/// Gender
	ESBLE_ATT_CHAR_GENDER                             = ESBLE_ATT_UUID_16(0x2A8C),
	/// Max Heart Rate
	ESBLE_ATT_CHAR_MAX_HEART_RATE                     = ESBLE_ATT_UUID_16(0x2A8D),
	/// Height
	ESBLE_ATT_CHAR_HEIGHT                             = ESBLE_ATT_UUID_16(0x2A8E),
	/// Hip Circumference
	ESBLE_ATT_CHAR_HIP_CIRCUMFERENCE                  = ESBLE_ATT_UUID_16(0x2A8F),
	/// Last Name
	ESBLE_ATT_CHAR_LAST_NAME                          = ESBLE_ATT_UUID_16(0x2A90),
	/// Maximum Recommended Heart Rate
	ESBLE_ATT_CHAR_MAXIMUM_RECOMMENDED_HEART_RATE     = ESBLE_ATT_UUID_16(0x2A91),
	/// Resting Heart Rate
	ESBLE_ATT_CHAR_RESTING_HEART_RATE                 = ESBLE_ATT_UUID_16(0x2A92),
	/// Sport Type For Aerobic And Anaerobic Thresholds
	ESBLE_ATT_CHAR_SPORT_TYPE_FOR_AEROBIC_AND_ANAEROBIC_THRESHOLDS = ESBLE_ATT_UUID_16(0x2A93),
	/// Three Zone Heart Rate Limits
	ESBLE_ATT_CHAR_THREE_ZONE_HEART_RATE_LIMITS       = ESBLE_ATT_UUID_16(0x2A94),
	/// Two Zone Heart Rate Limit
	ESBLE_ATT_CHAR_TWO_ZONE_HEART_RATE_LIMIT          = ESBLE_ATT_UUID_16(0x2A95),
	/// Vo2 Max
	ESBLE_ATT_CHAR_VO2_MAX                            = ESBLE_ATT_UUID_16(0x2A96),
	/// Waist Circumference
	ESBLE_ATT_CHAR_WAIST_CIRCUMFERENCE                = ESBLE_ATT_UUID_16(0x2A97),
	/// Weight
	ESBLE_ATT_CHAR_WEIGHT                             = ESBLE_ATT_UUID_16(0x2A98),
	/// Database Change Increment
	ESBLE_ATT_CHAR_DATABASE_CHANGE_INCREMENT          = ESBLE_ATT_UUID_16(0x2A99),
	/// User Index
	ESBLE_ATT_CHAR_USER_INDEX                         = ESBLE_ATT_UUID_16(0x2A9A),
	/// Body Composition Feature
	ESBLE_ATT_CHAR_BODY_COMPOSITION_FEATURE           = ESBLE_ATT_UUID_16(0x2A9B),
	/// Body Composition Measurement
	ESBLE_ATT_CHAR_BODY_COMPOSITION_MEASUREMENT       = ESBLE_ATT_UUID_16(0x2A9C),
	/// Weight Measurement
	ESBLE_ATT_CHAR_WEIGHT_MEASUREMENT                 = ESBLE_ATT_UUID_16(0x2A9D),
	/// Weight Scale Feature
	ESBLE_ATT_CHAR_WEIGHT_SCALE_FEATURE               = ESBLE_ATT_UUID_16(0x2A9E),
	/// User Control Point
	ESBLE_ATT_CHAR_USER_CONTROL_POINT                 = ESBLE_ATT_UUID_16(0x2A9F),
	/// Flux Density - 2D
	ESBLE_ATT_CHAR_MAGN_FLUX_2D                       = ESBLE_ATT_UUID_16(0x2AA0),
	/// Magnetic Flux Density - 3D
	ESBLE_ATT_CHAR_MAGN_FLUX_3D                       = ESBLE_ATT_UUID_16(0x2AA1),
	/// Language string
	ESBLE_ATT_CHAR_LANGUAGE                           = ESBLE_ATT_UUID_16(0x2AA2),
	/// Barometric Pressure Trend
	ESBLE_ATT_CHAR_BAR_PRES_TREND                     = ESBLE_ATT_UUID_16(0x2AA3),
	/// Central Address Resolution Support
	ESBLE_ATT_CHAR_CTL_ADDR_RESOL_SUPP                = ESBLE_ATT_UUID_16(0x2AA6),
	/// CGM Measurement
	ESBLE_ATT_CHAR_CGM_MEASUREMENT                    = ESBLE_ATT_UUID_16(0x2AA7),
	/// CGM Features
	ESBLE_ATT_CHAR_CGM_FEATURES                       = ESBLE_ATT_UUID_16(0x2AA8),
	/// CGM Status
	ESBLE_ATT_CHAR_CGM_STATUS                         = ESBLE_ATT_UUID_16(0x2AA9),
	/// CGM Session Start
	ESBLE_ATT_CHAR_CGM_SESSION_START                  = ESBLE_ATT_UUID_16(0x2AAA),
	/// CGM Session Run
	ESBLE_ATT_CHAR_CGM_SESSION_RUN                    = ESBLE_ATT_UUID_16(0x2AAB),
	/// CGM Specific Ops Control Point
	ESBLE_ATT_CHAR_CGM_SPECIFIC_OPS_CTRL_PT           = ESBLE_ATT_UUID_16(0x2AAC),
	/// Resolvable Private Address only
	ESBLE_ATT_CHAR_RSLV_PRIV_ADDR_ONLY                = ESBLE_ATT_UUID_16(0x2AC9),
	/// Mesh Provisioning Data In
	ESBLE_ATT_CHAR_MESH_PROV_DATA_IN                  = ESBLE_ATT_UUID_16(0x2ADB),
	/// Mesh Provisioning Data Out
	ESBLE_ATT_CHAR_MESH_PROV_DATA_OUT                 = ESBLE_ATT_UUID_16(0x2ADC),
	/// Mesh Proxy Data In
	ESBLE_ATT_CHAR_MESH_PROXY_DATA_IN                 = ESBLE_ATT_UUID_16(0x2ADD),
	/// Mesh Proxy Data Out
	ESBLE_ATT_CHAR_MESH_PROXY_DATA_OUT                = ESBLE_ATT_UUID_16(0x2ADE),
};

/// Format for Characteristic Presentation
enum {
	/// unsigned 1-bit: true or false
	ESBLE_ATT_FORMAT_BOOL     = 0x01,
	/// unsigned 2-bit integer
	ESBLE_ATT_FORMAT_2BIT,
	/// unsigned 4-bit integer
	ESBLE_ATT_FORMAT_NIBBLE,
	/// unsigned 8-bit integer
	ESBLE_ATT_FORMAT_UINT8,
	/// unsigned 12-bit integer
	ESBLE_ATT_FORMAT_UINT12,
	/// unsigned 16-bit integer
	ESBLE_ATT_FORMAT_UINT16,
	/// unsigned 24-bit integer
	ESBLE_ATT_FORMAT_UINT24,
	/// unsigned 32-bit integer
	ESBLE_ATT_FORMAT_UINT32,
	/// unsigned 48-bit integer
	ESBLE_ATT_FORMAT_UINT48,
	/// unsigned 64-bit integer
	ESBLE_ATT_FORMAT_UINT64,
	/// unsigned 128-bit integer
	ESBLE_ATT_FORMAT_UINT128,
	/// signed 8-bit integer
	ESBLE_ATT_FORMAT_SINT8,
	/// signed 12-bit integer
	ESBLE_ATT_FORMAT_SINT12,
	/// signed 16-bit integer
	ESBLE_ATT_FORMAT_SINT16,
	/// signed 24-bit integer
	ESBLE_ATT_FORMAT_SINT24,
	/// signed 32-bit integer
	ESBLE_ATT_FORMAT_SINT32,
	/// signed 48-bit integer
	ESBLE_ATT_FORMAT_SINT48,
	/// signed 64-bit integer
	ESBLE_ATT_FORMAT_SINT64,
	/// signed 128-bit integer
	ESBLE_ATT_FORMAT_SINT128,
	/// IEEE-754 32-bit floating point
	ESBLE_ATT_FORMAT_FLOAT32,
	/// IEEE-754 64-bit floating point
	ESBLE_ATT_FORMAT_FLOAT64,
	/// IEEE-11073 16-bit SFLOAT
	ESBLE_ATT_FORMAT_SFLOAT,
	/// IEEE-11073 32-bit FLOAT
	ESBLE_ATT_FORMAT_FLOAT,
	/// IEEE-20601 format
	ESBLE_ATT_FORMAT_DUINT16,
	/// UTF-8 string
	ESBLE_ATT_FORMAT_UTF8S,
	/// UTF-16 string
	ESBLE_ATT_FORMAT_UTF16S,
	/// Opaque structure
	ESBLE_ATT_FORMAT_STRUCT,
	/// Last format
	ESBLE_ATT_FORMAT_LAST
};


/// Client Characteristic Configuration Codes
enum att_ccc_val
{
	/// Stop notification/indication
	ESBLE_ATT_CCC_STOP_NTFIND = 0x0000,
	/// Start notification
	ESBLE_ATT_CCC_START_NTF,
	/// Start indication
	ESBLE_ATT_CCC_START_IND
};

/*
 * Type Definition
 ****************************************************************************************
 */

/// Attribute length type
typedef uint16_t esble_att_size_t;


/// UUID - 128-bit type
struct esble_att_uuid_128
{
	/// 128-bit UUID
	uint8_t uuid[ESBLE_ATT_UUID_128_LEN];
};

/// UUID - 32-bit type
struct esble_att_uuid_32
{
	/// 32-bit UUID
	uint8_t uuid[ESBLE_ATT_UUID_32_LEN];
};



/// Characteristic Value Descriptor
struct esble_att_char_desc
{
	/// properties
	uint8_t prop;
	/// attribute handle
	uint8_t attr_hdl[ESBLE_ATT_HANDLE_LEN];
	/// attribute type
	uint8_t attr_type[ESBLE_ATT_UUID_16_LEN];
};

/// Characteristic Value Descriptor
struct esble_att_char128_desc
{
	/// properties
	uint8_t prop;
	/// attribute handle
	uint8_t attr_hdl[ESBLE_ATT_HANDLE_LEN];
	/// attribute type
	uint8_t attr_type[ESBLE_ATT_UUID_128_LEN];
};

/// Service Value Descriptor - 16-bit
typedef uint16_t esble_att_svc_desc_t;

/// include service entry element
struct esble_att_incl_desc
{
	/// start handle value of included service
	uint16_t start_hdl;
	/// end handle value of included service
	uint16_t end_hdl;
	/// attribute value UUID
	uint16_t uuid;
};

/// include service entry element
struct esble_att_incl128_desc
{
	/// start handle value of included service
	uint16_t start_hdl;
	/// end handle value of included service
	uint16_t end_hdl;
};


// -------------------------- PDU HANDLER Definition  --------------------------

/// used to know if PDU handler has been found
#define ESBLE_ATT_PDU_HANDLER_NOT_FOUND       (0xff)

/// Format of a pdu handler function
typedef int (*esble_att_func_t)(uint8_t conidx, void *pdu);

/// Element of a pdu handler table.
struct esble_att_pdu_handler
{
	/// PDU identifier of the message
	uint8_t pdu_id;
	/// Pointer to the handler function for the pdu above.
	esble_att_func_t handler;
};


// --------------------------- Database permissions -----------------------------

/// Macro used to retrieve access permission rights
#define ESBLE_PERM_GET(perm, access)\
		(((perm) & (ESBLE_PERM_MASK_ ## access)) >> (ESBLE_PERM_POS_ ## access))

/// Macro used to set a permission value
#define ESBLE_PERM_SET(perm, access, value)\
	perm = ((perm & ~(ESBLE_PERM_MASK_ ## access)) | ((value << (ESBLE_PERM_POS_ ## access)) & (ESBLE_PERM_MASK_ ## access)))

/// Macro used to retrieve permission value from access and rights on attribute.
#define ESBLE_PERM(access, right) \
	(((ESBLE_PERM_RIGHT_ ## right) << (ESBLE_PERM_POS_ ## access)) & (ESBLE_PERM_MASK_ ## access))

/// Macro used know if permission is set or not.
#define ESBLE_PERM_IS_SET(perm, access, right) \
	(((perm) & (((ESBLE_PERM_RIGHT_ ## right) << (ESBLE_PERM_POS_ ## access))) \
				& (ESBLE_PERM_MASK_ ## access)) == ESBLE_PERM(access, right))

/// Macro used to create permission value
#define ESBLE_PERM_VAL(access, perm) \
	((((perm) << (ESBLE_PERM_POS_ ## access))) & (ESBLE_PERM_MASK_ ## access))


/// Retrieve attribute security level from attribute right and service right
#define ESBLE_ATT_GET_SEC_LVL(att_right, svc_right) \
	co_max(((att_right) & ESBLE_PERM_RIGHT_AUTH), ((svc_right) & ESBLE_PERM_RIGHT_AUTH));

/// Retrieve UUID LEN from UUID Length Permission
#define ESBLE_ATT_UUID_LEN(uuid_len_perm) ((uuid_len_perm == 0) ? ESBLE_ATT_UUID_16_LEN : \
		((uuid_len_perm == 1) ? ESBLE_ATT_UUID_32_LEN  :                        \
		((uuid_len_perm == 2) ? ESBLE_ATT_UUID_128_LEN : 0)))

/// Initialization of attribute element
#define ESBLE_ATT_ELEMT_INIT                                   {{NULL}, false}

/**
 *   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * |EXT | WS | I  | N  | WR | WC | RD | B  |    NP   |    IP   |   WP    |    RP   |
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 *
 * Bit [0-1]  : Read Permission         (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 * Bit [2-3]  : Write Permission        (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 * Bit [4-5]  : Indication Permission   (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 * Bit [6-7]  : Notification Permission (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = SEC_CON)
 *
 * Bit [8]    : Extended properties present (only relevant for a characteristic value)
 * Bit [9]    : Broadcast permission        (only relevant for a characteristic value)
 * Bit [10]   : Write Command accepted
 * Bit [11]   : Write Signed accepted
 * Bit [12]   : Write Request accepted
 * Bit [13]   : Encryption key Size must be 16 bytes
 */
enum esble_attm_perm_mask
{
	/// retrieve all permission info
	ESBLE_PERM_MASK_ALL           = 0x0000,
	/// Read Permission Mask
	ESBLE_PERM_MASK_RP            = 0x0003,
	ESBLE_PERM_POS_RP             = 0,
	/// Write Permission Mask
	ESBLE_PERM_MASK_WP            = 0x000C,
	ESBLE_PERM_POS_WP             = 2,
	/// Indication Access Mask
	ESBLE_PERM_MASK_IP            = 0x0030,
	ESBLE_PERM_POS_IP             = 4,
	/// Notification Access Mask
	ESBLE_PERM_MASK_NP            = 0x00C0,
	ESBLE_PERM_POS_NP             = 6,
	/// Broadcast descriptor present
	ESBLE_PERM_MASK_BROADCAST     = 0x0100,
	ESBLE_PERM_POS_BROADCAST      = 8,
	/// Read Access Mask
	ESBLE_PERM_MASK_RD            = 0x0200,
	ESBLE_PERM_POS_RD             = 9,
	/// Write Command Enabled attribute Mask
	ESBLE_PERM_MASK_WRITE_COMMAND = 0x0400,
	ESBLE_PERM_POS_WRITE_COMMAND  = 10,
	/// Write Request Enabled attribute Mask
	ESBLE_PERM_MASK_WRITE_REQ     = 0x0800,
	ESBLE_PERM_POS_WRITE_REQ      = 11,
	/// Notification Access Mask
	ESBLE_PERM_MASK_NTF           = 0x1000,
	ESBLE_PERM_POS_NTF            = 12,
	/// Indication Access Mask
	ESBLE_PERM_MASK_IND           = 0x2000,
	ESBLE_PERM_POS_IND            = 13,
	/// Write Signed Enabled attribute Mask
	ESBLE_PERM_MASK_WRITE_SIGNED  = 0x4000,
	ESBLE_PERM_POS_WRITE_SIGNED   = 14,
	/// Extended properties descriptor present
	ESBLE_PERM_MASK_EXT           = 0x8000,
	ESBLE_PERM_POS_EXT            = 15,

	/// Properties
	ESBLE_PERM_MASK_PROP          = 0xFF00,
	ESBLE_PERM_POS_PROP           = 8,
};

/**
 * Value permission bit field
 *
 *   15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * | RI |UUID_LEN |EKS |    MAX_LEN (RI = 1) / Value Offset  (RI = 0)              |
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 *
 * Bit [0-11] : Maximum Attribute Length or Value Offset pointer
 * Bit [12]   : Encryption key Size must be 16 bytes
 * Bit [14-13]: UUID Length             (0 = 16 bits, 1 = 32 bits, 2 = 128 bits, 3 = RFU)
 * Bit [15]   : Trigger Read Indication (0 = Value present in Database, 1 = Value not present in Database)
 */
enum esble_attm_value_perm_mask
{
	/// Maximum Attribute Length
	ESBLE_PERM_MASK_MAX_LEN     = 0x0FFF,
	ESBLE_PERM_POS_MAX_LEN      = 0,
	/// Attribute value Offset
	ESBLE_PERM_MASK_VAL_OFFSET  = 0x0FFF,
	ESBLE_PERM_POS_VAL_OFFSET   = 0,
	/// Check Encryption key size Mask
	ESBLE_PERM_MASK_EKS         = 0x1000,
	ESBLE_PERM_POS_EKS          = 12,
	/// UUID Length
	ESBLE_PERM_MASK_UUID_LEN    = 0x6000,
	ESBLE_PERM_POS_UUID_LEN     = 13,
	/// Read trigger Indication
	ESBLE_PERM_MASK_RI          = 0x8000,
	ESBLE_PERM_POS_RI           = 15,
};


/**
 * Service permissions
 *
 *    7    6    5    4    3    2    1    0
 * +----+----+----+----+----+----+----+----+
 * |SEC |UUID_LEN |DIS |  AUTH   |EKS | MI |
 * +----+----+----+----+----+----+----+----+
 *
 * Bit [0]  : Task that manage service is multi-instantiated (Connection index is conveyed)
 * Bit [1]  : Encryption key Size must be 16 bytes
 * Bit [2-3]: Service Permission      (0 = NO_AUTH, 1 = UNAUTH, 2 = AUTH, 3 = Secure Connect)
 * Bit [4]  : Disable the service
 * Bit [5-6]: UUID Length             (0 = 16 bits, 1 = 32 bits, 2 = 128 bits, 3 = RFU)
 * Bit [7]  : Secondary Service       (0 = Primary Service, 1 = Secondary Service)
 */
enum esble_attm_svc_perm_mask
{
	/// Task that manage service is multi-instantiated
	ESBLE_PERM_MASK_SVC_MI        = 0x01,
	ESBLE_PERM_POS_SVC_MI         = 0,
	/// Check Encryption key size for service Access
	ESBLE_PERM_MASK_SVC_EKS       = 0x02,
	ESBLE_PERM_POS_SVC_EKS        = 1,
	/// Service Permission authentication
	ESBLE_PERM_MASK_SVC_AUTH      = 0x0C,
	ESBLE_PERM_POS_SVC_AUTH       = 2,
	/// Disable the service
	ESBLE_PERM_MASK_SVC_DIS       = 0x10,
	ESBLE_PERM_POS_SVC_DIS        = 4,
	/// Service UUID Length
	ESBLE_PERM_MASK_SVC_UUID_LEN  = 0x60,
	ESBLE_PERM_POS_SVC_UUID_LEN   = 5,
	/// Service type Secondary
	ESBLE_PERM_MASK_SVC_SECONDARY = 0x80,
	ESBLE_PERM_POS_SVC_SECONDARY  = 7,
};


/// Attribute & Service access mode
enum
{
	/// Disable access
	ESBLE_PERM_RIGHT_DISABLE  = 0,
	/// Enable access
	ESBLE_PERM_RIGHT_ENABLE   = 1,
};

/// Attribute & Service access rights
enum
{
	/// No Authentication
	ESBLE_PERM_RIGHT_NO_AUTH  = 0,
	/// Access Requires Unauthenticated link
	ESBLE_PERM_RIGHT_UNAUTH   = 1,
	/// Access Requires Authenticated link
	ESBLE_PERM_RIGHT_AUTH     = 2,
	/// Access Requires Secure Connection link
	ESBLE_PERM_RIGHT_SEC_CON  = 3,
};

/// Attribute & Service UUID Length
enum
{
	/// 16  bits UUID
	ESBLE_PERM_UUID_16         = 0,
	ESBLE_PERM_RIGHT_UUID_16   = 0,
	/// 32  bits UUID
	ESBLE_PERM_UUID_32         = 1,
	ESBLE_PERM_RIGHT_UUID_32   = 1,
	/// 128 bits UUID
	ESBLE_PERM_UUID_128        = 2,
	ESBLE_PERM_RIGHT_UUID_128  = 2,
	/// Invalid
	ESBLE_PERM_UUID_RFU        = 3,
};

/// execute flags
enum
{
	/// Cancel All the Reliable Writes
	ESBLE_ATT_CANCEL_ALL_PREPARED_WRITES = 0x00,
	/// Write All the Reliable Writes
	ESBLE_ATT_EXECUTE_ALL_PREPARED_WRITES
};



/// @} ATT
#endif // ATT_H_
