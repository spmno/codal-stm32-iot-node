#ifndef __GATT_CALLBACK_PARAM_TYPES_H__
#define __GATT_CALLBACK_PARAM_TYPES_H__
 
#include "Gap.h"
struct GattWriteCallbackParams {
    /**
     * Enumeration for write operations.
     */
    enum class WriteOp_t {
        OP_INVALID               = 0x00,  /**< Invalid operation. */
        OP_WRITE_REQ             = 0x01,  /**< Write request. */
        OP_WRITE_CMD             = 0x02,  /**< Write command. */
        OP_SIGN_WRITE_CMD        = 0x03,  /**< Signed write command. */
        OP_PREP_WRITE_REQ        = 0x04,  /**< Prepare write request. */
        OP_EXEC_WRITE_REQ_CANCEL = 0x05,  /**< Execute write request: cancel all prepared writes. */
        OP_EXEC_WRITE_REQ_NOW    = 0x06,  /**< Execute write request: immediately execute all prepared writes. */
    };
 
    Gap::Handle_t            connHandle; /**< The handle of the connection that triggered the event */
    GattAttribute::Handle_t  handle;     /**< Attribute Handle to which the write operation applies. */
    WriteOp_t                writeOp;    /**< Type of write operation. */
    uint16_t                 offset;     /**< Offset for the write operation. */
    uint16_t                 len;        /**< Length (in bytes) of the data to write. */
    /**
     * Pointer to the data to write.
     *
     * @note Data might not persist beyond the callback; make a local copy if
     *       needed.
     */
    const uint8_t           *data;
};
 
struct GattReadCallbackParams {
    Gap::Handle_t            connHandle; /**< The handle of the connection that triggered the event */
    GattAttribute::Handle_t  handle;     /**< Attribute Handle to which the read operation applies. */
    uint16_t                 offset;     /**< Offset for the read operation. */
    uint16_t                 len;        /**< Length (in bytes) of the data to read. */
    /**
     * Pointer to the data read.
     *
     * @note Data might not persist beyond the callback; make a local copy if
     *       needed.
     */
    const uint8_t           *data;
};
 
enum class GattAuthCallbackReply_t {
    AUTH_CALLBACK_REPLY_SUCCESS                       = 0x00,    /**< Success. */
    AUTH_CALLBACK_REPLY_ATTERR_INVALID_HANDLE         = 0x0101,  /**< ATT Error: Invalid attribute handle. */
    AUTH_CALLBACK_REPLY_ATTERR_READ_NOT_PERMITTED     = 0x0102,  /**< ATT Error: Read not permitted. */
    AUTH_CALLBACK_REPLY_ATTERR_WRITE_NOT_PERMITTED    = 0x0103,  /**< ATT Error: Write not permitted. */
    AUTH_CALLBACK_REPLY_ATTERR_INSUF_AUTHENTICATION   = 0x0105,  /**< ATT Error: Authenticated link required. */
    AUTH_CALLBACK_REPLY_ATTERR_INVALID_OFFSET         = 0x0107,  /**< ATT Error: The specified offset was past the end of the attribute. */
    AUTH_CALLBACK_REPLY_ATTERR_INSUF_AUTHORIZATION    = 0x0108,  /**< ATT Error: Used in ATT as "insufficient authorization". */
    AUTH_CALLBACK_REPLY_ATTERR_PREPARE_QUEUE_FULL     = 0x0109,  /**< ATT Error: Used in ATT as "prepare queue full". */
    AUTH_CALLBACK_REPLY_ATTERR_ATTRIBUTE_NOT_FOUND    = 0x010A,  /**< ATT Error: Used in ATT as "attribute not found". */
    AUTH_CALLBACK_REPLY_ATTERR_ATTRIBUTE_NOT_LONG     = 0x010B,  /**< ATT Error: Attribute cannot be read or written using read/write blob requests. */
    AUTH_CALLBACK_REPLY_ATTERR_INVALID_ATT_VAL_LENGTH = 0x010D,  /**< ATT Error: Invalid value size. */
    AUTH_CALLBACK_REPLY_ATTERR_INSUF_RESOURCES        = 0x0111,  /**< ATT Error: Encrypted link required. */
};
 
struct GattWriteAuthCallbackParams {
    Gap::Handle_t            connHandle; /**< The handle of the connection that triggered the event */
    GattAttribute::Handle_t  handle;     /**< Attribute Handle to which the write operation applies. */
    uint16_t                 offset;     /**< Offset for the write operation. */
    uint16_t                 len;        /**< Length of the incoming data. */
    const uint8_t           *data;       /**< Incoming data, variable length. */
    /**
     * This is the out parameter that the callback needs to set to
     * AUTH_CALLBACK_REPLY_SUCCESS for the request to proceed.
     */
    GattAuthCallbackReply_t  authorizationReply;
};
 
struct GattReadAuthCallbackParams {
    Gap::Handle_t            connHandle; /**< The handle of the connection that triggered the event */
    GattAttribute::Handle_t  handle;     /**< Attribute Handle to which the read operation applies. */
    uint16_t                 offset;     /**< Offset for the read operation. */
    uint16_t                 len;        /**< Optional: new length of the outgoing data. */
    uint8_t                 *data;       /**< Optional: new outgoing data. Leave at NULL if data is unchanged. */
    /**
     * This is the out parameter that the callback needs to set to
     * AUTH_CALLBACK_REPLY_SUCCESS for the request to proceed.
     */
    GattAuthCallbackReply_t  authorizationReply;
};
 
/**
 * For encapsulating handle-value update events (notifications or indications)
 * generated at the remote server.
 */
struct GattHVXCallbackParams {
  Gap::Handle_t            connHandle; /**< The handle of the connection that triggered the event */
  GattAttribute::Handle_t  handle;     /**< Attribute Handle to which the HVx operation applies. */
  HVXType_t                type;       /**< Indication or Notification, see HVXType_t. */
  uint16_t                 len;        /**< Attribute data length. */
  const uint8_t           *data;       /**< Attribute data, variable length. */
};
 
#endif /*__GATT_CALLBACK_PARAM_TYPES_H__*/