/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2014 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

#include <libfreenect2/resource.h>
#include <string>
#include <cstring>
#include <iostream>

namespace libfreenect2
{

struct ResourceDescriptor
{
  const char *filename;
  const unsigned char *data;
  size_t length;
};

#ifdef RESOURCES_INC
#include "resources.inc"
#else
ResourceDescriptor resource_descriptors[] = {};
#endif

bool loadResource(const std::string &name, unsigned char const**data, size_t *length)
{
  bool result = false;

  for(int i = 0; i < resource_descriptors_length; ++i)
  {
    if(name.compare(resource_descriptors[i].filename) == 0)
    {
      *data = resource_descriptors[i].data;
      *length = resource_descriptors[i].length;
      result = true;
      break;
    }
  }
  return result;
}

bool loadBufferFromResources(const std::string &filename, unsigned char *buffer, const size_t n)
{
  size_t length = 0;
  const unsigned char *data = NULL;

  if(!loadResource(filename, &data, &length))
  {
    std::cerr << "loadBufferFromResources: failed to load resource: " << filename << std::endl;
    return false;
  }

  if(length != n)
  {
    std::cerr << "loadBufferFromResources: wrong size of resource: " << filename << std::endl;
    return false;
  }

  memcpy(buffer, data, length);
  return true;
}

} /* namespace libfreenect2 */
