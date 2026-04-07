#include <sys/stat.h>

#include "kmod/uxdevvfs.h"
#include "kmod/uxlog.h"

int
umcxray_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
    switch (cmd) {
    case DDI_ATTACH:
        if (ddi_create_minor_node(dip, "umcxray", S_IFCHR, 0,
            DDI_PSEUDO, 0) == DDI_FAILURE) {
            WARN("ddi_create_minor_node() failed");
            return DDI_FAILURE;
        }

        ddi_report_dev(dip);
        return DDI_SUCCESS;

    default:
        return DDI_FAILURE;
    }
}

int
umcxray_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
    switch (cmd) {
    case DDI_DETACH:
        ddi_remove_minor_node(dip, NULL);
        return DDI_SUCCESS;

    default:
        return DDI_FAILURE;
    }
}
