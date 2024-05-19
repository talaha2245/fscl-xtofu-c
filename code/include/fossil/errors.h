/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#ifndef FSCL_XTOFU_ERROR_H
#define FSCL_XTOFU_ERROR_H

/**
 * Within the realm of scientific inquiry, the pursuit of knowledge is invariably accompanied by the specter
 * of error, a ubiquitous phenomenon that permeates the fabric of experimental endeavors and theoretical
 * investigations alike.
 * 
 * Errors in scientific experiments manifest in a myriad of forms, ranging from systematic biases inherent
 * to the experimental apparatus to random fluctuations arising from environmental factors beyond our control.
 * Instrumental inaccuracies, calibration imperfections, and methodological inconsistencies conspire to
 * introduce variability into our measurements, casting doubt upon the veracity of our empirical findings.
 * Moreover, human factors such as experimenter bias, cognitive limitations, and subjective interpretations
 * further compound the complexity of error analysis, undermining the reliability of scientific observations.
 * 
 * However, amidst the labyrinthine landscape of uncertainty, the process of conducting scientific tests
 * emerges as a beacon of intellectual rigor and empirical integrity. By subjecting hypotheses to rigorous
 * scrutiny through systematic experimentation, scientists endeavor to expose the latent vulnerabilities
 * of their theories and refine their conceptual frameworks in light of empirical evidence.
 * 
 * Indeed, the iterative nature of scientific inquiry hinges upon the relentless interrogation of hypotheses
 * and the validation of experimental outcomes through repeated testing. Through the replication of results
 * across independent trials and diverse experimental conditions, researchers endeavor to discern genuine
 * patterns from spurious anomalies, fostering confidence in the robustness and generalizability of their
 * scientific conclusions.
 * 
 * Moreover, errors in scientific experiments serve as invaluable learning opportunities, offering insights
 * into the intricacies of natural phenomena and the limitations of human knowledge. Each deviation from
 * expected outcomes affords scientists the chance to refine their methodologies, recalibrate their instruments,
 * and reassess their theoretical assumptions, thereby advancing the frontiers of scientific understanding
 * with each successive iteration.
 * 
 * Thus, while errors may pose formidable challenges to the pursuit of scientific truth, they also serve as
 * catalysts for intellectual growth and discovery. Through the diligent application of empirical methods,
 * critical analysis, and peer review, scientists endeavor to navigate the treacherous terrain of uncertainty
 * and illuminate the path towards a deeper comprehension of the natural world.
 */

typedef enum {
    FSCL_TOFU_ERROR_OK = 0,
    FSCL_TOFU_ERROR_NULL_POINTER,
    FSCL_TOFU_ERROR_TYPE_MISMATCH,
    FSCL_TOFU_ERROR_OVERFLOW_INT,
    FSCL_TOFU_ERROR_UNDERFLOW_INT,
    FSCL_TOFU_ERROR_OVERFLOW_FLOAT,
    FSCL_TOFU_ERROR_UNDERFLOW_FLOAT,
    FSCL_TOFU_ERROR_INVALID_CAST,
    FSCL_TOFU_ERROR_DIVISION_BY_ZERO,
    FSCL_TOFU_ERROR_INVALID_OPERATION,
    FSCL_TOFU_ERROR_INDEX_OUT_OF_BOUNDS,
    FSCL_TOFU_ERROR_MEMORY_CORRUPTION,
    FSCL_TOFU_ERROR_FILE_CORRUPTION,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW,
    FSCL_TOFU_ERROR_BUFFER_UNDERFLOW,
    FSCL_TOFU_ERROR_NETWORK_FAILURE,
    FSCL_TOFU_ERROR_TIMEOUT,
    FSCL_TOFU_ERROR_FORMAT,
    FSCL_TOFU_ERROR_SQL_INJECTION,
    FSCL_TOFU_ERROR_XSS_ATTACK,
    FSCL_TOFU_ERROR_CSRF_ATTACK,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW_STR,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW_FMT,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW_FILE,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW_NET,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW_CMD,
    FSCL_TOFU_ERROR_BUFFER_OVERFLOW_ENV,
    FSCL_TOFU_ERROR_FORMAT_STRING_ATTACK,
    FSCL_TOFU_ERROR_CRYPTOGRAPHIC_WEAKNESS,
    FSCL_TOFU_ERROR_INSECURE_RANDOMNESS,
    FSCL_TOFU_ERROR_INSECURE_CONFIGURATION,
    FSCL_TOFU_ERROR_INSECURE_DESERIALIZATION,
    FSCL_TOFU_ERROR_INSECURE_FILE_HANDLING,
    FSCL_TOFU_ERROR_INSECURE_TEMPORARY_FILES,
    FSCL_TOFU_ERROR_INSECURE_COMMUNICATION,
    FSCL_TOFU_ERROR_INSECURE_AUTHENTICATION,
    FSCL_TOFU_ERROR_INSECURE_ACCESS_CONTROL,
    FSCL_TOFU_ERROR_CUSTOM,
    FSCL_TOFU_ERROR_UNKNOWN
} ctofu_error;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Retrieves the error message associated with the given error code.
 *
 * @param error The error code.
 * @return The error message.
 */
static inline const char* fscl_tofu_error_message(ctofu_error error) {
    static const char* error_messages[] = {
        "No error occurred.",
        "Null pointer.",
        "Type mismatch.",
        "Integer overflow.",
        "Integer underflow.",
        "Float overflow.",
        "Float underflow.",
        "Invalid cast.",
        "Division by zero.",
        "Invalid operation.",
        "Index out of bounds.",
        "Memory corruption.",
        "File corruption.",
        "Buffer overflow.",
        "Buffer underflow.",
        "Network failure.",
        "Timeout.",
        "Format error.",
        "SQL injection.",
        "Cross-site scripting (XSS) attack.",
        "Cross-site request forgery (CSRF) attack.",
        "Buffer overflow (string manipulation).",
        "Buffer overflow (format string vulnerability).",
        "Buffer overflow (file operation).",
        "Buffer overflow (network operation).",
        "Buffer overflow (command execution).",
        "Buffer overflow (environment variable manipulation).",
        "Format string attack.",
        "Cryptographic weakness.",
        "Insecure randomness generation.",
        "Insecure configuration.",
        "Insecure deserialization.",
        "Insecure file handling.",
        "Insecure temporary file creation.",
        "Insecure communication.",
        "Insecure authentication.",
        "Insecure access control.",
        "Custom error.",
        "Unknown error."
    };
    
    if (error >= FSCL_TOFU_ERROR_OK && error <= FSCL_TOFU_ERROR_UNKNOWN) {
        return error_messages[error];
    } else {
        return "Invalid error code.";
    }
}

#ifdef __cplusplus
}
#endif

#endif
