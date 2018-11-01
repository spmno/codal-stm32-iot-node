#ifndef __GATT_ATTRIBUTE_H__
#define __GATT_ATTRIBUTE_H__
 
#include "UUID.h"
 
/**
 * Instances of this class encapsulate the data that belongs to a Bluetooth Low
 * Energy attribute.
 */
class GattAttribute {
public:
    /**
     * Type for the handle or ID of the attribute in the ATT table. These are
     * unique and are usually generated by the underlying BLE stack.
     */
    typedef uint16_t Handle_t;
    /**
     * Define the value of an invalid attribute handle.
     */
    static const Handle_t INVALID_HANDLE = 0x0000;
 
public:
    /**
     *  @brief  Creates a new GattAttribute using the specified
     *          UUID, value length, and inital value.
     *
     *  @param[in]  uuid
     *              The UUID to use for this attribute.
     *  @param[in]  valuePtr
     *              The memory holding the initial value.
     *  @param[in]  len
     *              The length in bytes of this attribute's value.
     *  @param[in]  maxLen
     *              The max length in bytes of this attribute's value.
     *  @param[in]  hasVariableLen
     *              Whether the attribute's value length changes overtime.
     *
     *  @section EXAMPLE
     *
     *  @code
     *
     *  // UUID = 0x2A19, Min length 2, Max len = 2
     *  GattAttribute attr = GattAttribute(0x2A19, &someValue, 2, 2);
     *
     *  @endcode
     */
    GattAttribute(const UUID &uuid, uint8_t *valuePtr = NULL, uint16_t len = 0, uint16_t maxLen = 0, bool hasVariableLen = true) :
        _uuid(uuid), _valuePtr(valuePtr), _lenMax(maxLen), _len(len), _hasVariableLen(hasVariableLen), _handle() {
        /* Empty */
    }
 
public:
    /**
     * Get the attribute's handle in the ATT table.
     *
     * @return The attribute's handle.
     */
    Handle_t getHandle(void) const {
        return _handle;
    }
 
    /**
     * The UUID of the characteristic that this attribute belongs to.
     *
     * @return The characteristic's UUID.
     */
    const UUID &getUUID(void) const {
        return _uuid;
    }
 
    /**
     * Get the current length of the attribute value.
     *
     * @return The current length of the attribute value.
     */
    uint16_t getLength(void) const {
        return _len;
    }
 
    /**
     * Get the maximum length of the attribute value.
     *
     * The maximum length of the attribute value.
     */
    uint16_t getMaxLength(void) const {
        return _lenMax;
    }
 
    /**
     * Get a pointer to the current length of the attribute value.
     *
     * @return A pointer to the current length of the attribute value.
     */
    uint16_t *getLengthPtr(void) {
        return &_len;
    }
 
    /**
     * Set the attribute handle.
     *
     * @param[in] id
     *              The new attribute handle.
     */
    void setHandle(Handle_t id) {
        _handle = id;
    }
 
    /**
     * Get a pointer to the attribute value.
     *
     * @return A pointer to the attribute value.
     */
    uint8_t *getValuePtr(void) {
        return _valuePtr;
    }
 
    /**
     * Check whether the length of the attribute's value can change over time.
     *
     * @return true if the attribute has variable length, false otherwise.
     */
    bool hasVariableLength(void) const {
        return _hasVariableLen;
    }
 
private:
    /**
     * Characteristic's UUID.
     */
    UUID      _uuid;
    /**
     * Pointer to the attribute's value.
     */
    uint8_t  *_valuePtr;
    /**
     * Maximum length of the value pointed to by GattAttribute::_valuePtr.
     */
    uint16_t  _lenMax;
    /**
     * Current length of the value pointed to by GattAttribute::_valuePtr.
     */
    uint16_t  _len;
    /**
     * Whether the length of the value can change over time.
     */
    bool      _hasVariableLen;
    /**
     * The attribute's handle in the ATT table.
     */
    Handle_t  _handle;
 
private:
    /* Disallow copy and assignment. */
    GattAttribute(const GattAttribute &);
    GattAttribute& operator=(const GattAttribute &);
};
 
#endif /* ifndef __GATT_ATTRIBUTE_H__ */