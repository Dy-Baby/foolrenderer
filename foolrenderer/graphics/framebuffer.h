// Copyright (c) Caden Ji. All rights reserved.
//
// Licensed under the MIT License. See LICENSE file in the project root for
// license information.

#ifndef FOOLRENDERER_GRAPHICS_FRAMEBUFFER_H_
#define FOOLRENDERER_GRAPHICS_FRAMEBUFFER_H_

#include <stdbool.h>
#include <stdint.h>

#include "graphics/texture.h"

enum attachment_type { COLOR_ATTACHMENT, DEPTH_ATTACHMENT };

///
/// \brief A framebuffer is a collection of buffers that can be used as the
///        destination for rendering.
///
struct framebuffer;

///
/// \brief Creates a framebuffer.
///
/// The created framebuffer does not contain any buffer. It can only be used
/// after attaching at least one buffer to the framebuffer using the
/// attach_texture_to_framebuffer() function.
///
/// Returns a null pointer if memory allocation fails.
///
/// \return Returns a framebuffer pointer on success, null pointer on failure.
///
struct framebuffer *create_framebuffer(void);

///
/// \brief Release the memory pointed to by framebuffer.
///
/// The buffer attached to the framebuffer will not be released. If framebuffer
/// is a null pointer, the function does nothing.
///
/// \param framebuffer Pointer to the framebuffer to destroy.
///
void destroy_framebuffer(struct framebuffer *framebuffer);

///
/// \brief Attaches a texture as one of the logical buffers of the framebuffer.
///
/// Different attachment type correspond to specific valid texture types:
///
/// Attachment Type  | Texture Format
/// ---------------- | -----------------------------
/// COLOR_ATTACHMENT | TEXTURE_FORMAT_RGBA8, TEXTURE_FORMAT_SRGB8_A8
/// DEPTH_ATTACHMENT | TEXTURE_FORMAT_DEPTH_FLOAT
///
/// If the texture is a null pointer detachs the current type buffer. Fails if
/// framebuffer is a null pointer. Fails if the attachment type is invalid.
/// Fails if the attached texture type is invalid.
///
/// If the attached texture size is inconsistent, the width and height of the
/// framebuffer will use the minimum of all texture sizes respectively.
///
/// \param framebuffer Pointer to the framebuffer to attach to.
/// \param attachment The type of buffer will to be attached.
/// \param texture Pointer to the texture to attach.
/// \return Returns true on success, false on failure.
///
bool attach_texture_to_framebuffer(struct framebuffer *framebuffer,
                                   enum attachment_type attachment,
                                   struct texture *texture);

///
/// \brief Sets clear values for the color buffers.
///
/// Sets the red, green, bule and alpha values used by clear_framebuffer() to
/// clear the color buffers. The set values are clamped to the range [0,1] and
/// the initial values are all 0.
///
/// \param red The R component of the color value.
/// \param green The G component of the color value.
/// \param blue The B component of the color value.
/// \param alpha The A component of the color value.
///
void set_clear_color(float red, float green, float blue, float alpha);

///
/// \brief Uses preset values to clear all buffers in the framebuffer.
///
/// Each pixel of the color buffer will be cleared using the value previously
/// set via the set_clear_color() function. For depth buffers, a fixed value of
/// 1 will be used to clear each pixel. If framebuffer is a null pointer, the
/// function does nothing.
///
/// \param framebuffer Pointer to the framebuffer to clear.
///
void clear_framebuffer(struct framebuffer *framebuffer);

///
/// \brief Gets the width of the framebuffer.
///
/// If framebuffer does not contain any buffer, returns 0. The behavior is
/// undefined if framebuffer is a null pointer.
///
/// \param framebuffer Pointer to the framebuffer to get.
/// \return Returns the width of the framebuffer.
///
uint32_t get_framebuffer_width(const struct framebuffer *framebuffer);

///
/// \brief Gets the height of the framebuffer.
///
/// If framebuffer does not contain any buffer, returns 0. The behavior is
/// undefined if framebuffer is a null pointer.
///
/// \param framebuffer Pointer to the framebuffer to get.
/// \return Returns the height of the framebuffer.
///
uint32_t get_framebuffer_height(const struct framebuffer *framebuffer);

///
/// \brief Gets the buffer of the specified attachment type from the
///        framebuffer.
///
/// Returns a null pointer if framebuffer is a null pointer. Returns a null
/// pointer if the attachment type is invalid. Returns a null pointer if the
/// buffer for the specified attachment type is empty.
///
/// \param framebuffer Pointer to the framebuffer to get from.
/// \param attachment The type of buffer to get.
/// \return Returns the pointer of the buffer.
///
struct texture *get_framebuffer_attachment(struct framebuffer *framebuffer,
                                           enum attachment_type attachment);

#endif  // FOOLRENDERER_GRAPHICS_FRAMEBUFFER_H_
